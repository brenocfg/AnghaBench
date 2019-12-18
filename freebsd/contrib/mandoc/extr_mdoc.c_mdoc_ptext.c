#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct roff_node {scalar_t__ tok; scalar_t__ type; scalar_t__ end; char* string; int flags; TYPE_5__* parent; TYPE_2__* norm; } ;
struct roff_man {int flags; struct roff_node* last; int /*<<< orphan*/  next; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* fp ) (struct roff_man*,int /*<<< orphan*/ ,int,int,int*,char*) ;} ;
struct TYPE_11__ {scalar_t__ tok; TYPE_4__* norm; } ;
struct TYPE_9__ {scalar_t__ type; } ;
struct TYPE_10__ {TYPE_3__ Bl; } ;
struct TYPE_7__ {scalar_t__ type; } ;
struct TYPE_8__ {TYPE_1__ Bl; } ;

/* Variables and functions */
 scalar_t__ ENDBODY_NOT ; 
 scalar_t__ LIST_column ; 
 int /*<<< orphan*/  MANDOCERR_EOS ; 
 int /*<<< orphan*/  MANDOCERR_FI_BLANK ; 
 int /*<<< orphan*/  MANDOCERR_SPACE_EOL ; 
 scalar_t__ MDOC_Bl ; 
 int MDOC_FREECOL ; 
 int /*<<< orphan*/  MDOC_It ; 
 int NODE_ENDED ; 
 int NODE_EOS ; 
 int NODE_VALID ; 
 scalar_t__ ROFFT_BODY ; 
#define  ROFFT_TEXT 128 
 int /*<<< orphan*/  ROFF_NEXT_SIBLING ; 
 int ROFF_NOFILL ; 
 int /*<<< orphan*/  ROFF_sp ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ isalnum (unsigned char) ; 
 scalar_t__ isupper (unsigned char) ; 
 scalar_t__ mandoc_eos (char*,size_t) ; 
 int /*<<< orphan*/  mandoc_msg (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 TYPE_6__* mdoc_macro (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roff_elem_alloc (struct roff_man*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roff_word_alloc (struct roff_man*,int,int,char*) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  stub1 (struct roff_man*,int /*<<< orphan*/ ,int,int,int*,char*) ; 

__attribute__((used)) static int
mdoc_ptext(struct roff_man *mdoc, int line, char *buf, int offs)
{
	struct roff_node *n;
	const char	 *cp, *sp;
	char		 *c, *ws, *end;

	n = mdoc->last;

	/*
	 * If a column list contains plain text, assume an implicit item
	 * macro.  This can happen one or more times at the beginning
	 * of such a list, intermixed with non-It mdoc macros and with
	 * nodes generated on the roff level, for example by tbl.
	 */

	if ((n->tok == MDOC_Bl && n->type == ROFFT_BODY &&
	     n->end == ENDBODY_NOT && n->norm->Bl.type == LIST_column) ||
	    (n->parent != NULL && n->parent->tok == MDOC_Bl &&
	     n->parent->norm->Bl.type == LIST_column)) {
		mdoc->flags |= MDOC_FREECOL;
		(*mdoc_macro(MDOC_It)->fp)(mdoc, MDOC_It,
		    line, offs, &offs, buf);
		return 1;
	}

	/*
	 * Search for the beginning of unescaped trailing whitespace (ws)
	 * and for the first character not to be output (end).
	 */

	/* FIXME: replace with strcspn(). */
	ws = NULL;
	for (c = end = buf + offs; *c; c++) {
		switch (*c) {
		case ' ':
			if (NULL == ws)
				ws = c;
			continue;
		case '\t':
			/*
			 * Always warn about trailing tabs,
			 * even outside literal context,
			 * where they should be put on the next line.
			 */
			if (NULL == ws)
				ws = c;
			/*
			 * Strip trailing tabs in literal context only;
			 * outside, they affect the next line.
			 */
			if (mdoc->flags & ROFF_NOFILL)
				continue;
			break;
		case '\\':
			/* Skip the escaped character, too, if any. */
			if (c[1])
				c++;
			/* FALLTHROUGH */
		default:
			ws = NULL;
			break;
		}
		end = c + 1;
	}
	*end = '\0';

	if (ws)
		mandoc_msg(MANDOCERR_SPACE_EOL, line, (int)(ws - buf), NULL);

	/*
	 * Blank lines are allowed in no-fill mode
	 * and cancel preceding \c,
	 * but add a single vertical space elsewhere.
	 */

	if (buf[offs] == '\0' && (mdoc->flags & ROFF_NOFILL) == 0) {
		switch (mdoc->last->type) {
		case ROFFT_TEXT:
			sp = mdoc->last->string;
			cp = end = strchr(sp, '\0') - 2;
			if (cp < sp || cp[0] != '\\' || cp[1] != 'c')
				break;
			while (cp > sp && cp[-1] == '\\')
				cp--;
			if ((end - cp) % 2)
				break;
			*end = '\0';
			return 1;
		default:
			break;
		}
		mandoc_msg(MANDOCERR_FI_BLANK, line, (int)(c - buf), NULL);
		roff_elem_alloc(mdoc, line, offs, ROFF_sp);
		mdoc->last->flags |= NODE_VALID | NODE_ENDED;
		mdoc->next = ROFF_NEXT_SIBLING;
		return 1;
	}

	roff_word_alloc(mdoc, line, offs, buf+offs);

	if (mdoc->flags & ROFF_NOFILL)
		return 1;

	/*
	 * End-of-sentence check.  If the last character is an unescaped
	 * EOS character, then flag the node as being the end of a
	 * sentence.  The front-end will know how to interpret this.
	 */

	assert(buf < end);

	if (mandoc_eos(buf+offs, (size_t)(end-buf-offs)))
		mdoc->last->flags |= NODE_EOS;

	for (c = buf + offs; c != NULL; c = strchr(c + 1, '.')) {
		if (c - buf < offs + 2)
			continue;
		if (end - c < 3)
			break;
		if (c[1] != ' ' ||
		    isalnum((unsigned char)c[-2]) == 0 ||
		    isalnum((unsigned char)c[-1]) == 0 ||
		    (c[-2] == 'n' && c[-1] == 'c') ||
		    (c[-2] == 'v' && c[-1] == 's'))
			continue;
		c += 2;
		if (*c == ' ')
			c++;
		if (*c == ' ')
			c++;
		if (isupper((unsigned char)(*c)))
			mandoc_msg(MANDOCERR_EOS, line, (int)(c - buf), NULL);
	}

	return 1;
}