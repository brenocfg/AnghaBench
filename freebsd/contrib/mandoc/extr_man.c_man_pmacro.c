#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct roff_node {scalar_t__ type; int /*<<< orphan*/  tok; int /*<<< orphan*/  parent; TYPE_2__* prev; } ;
struct roff_man {int flags; struct roff_node* last; scalar_t__ quick; int /*<<< orphan*/  manmac; } ;
typedef  enum roff_tok { ____Placeholder_roff_tok } roff_tok ;
struct TYPE_6__ {int flags; int /*<<< orphan*/  (* fp ) (struct roff_man*,int,int,int,int*,char*) ;} ;
struct TYPE_5__ {TYPE_1__* child; } ;
struct TYPE_4__ {int /*<<< orphan*/  string; } ;

/* Variables and functions */
 int /*<<< orphan*/  MANDOCERR_MACRO ; 
 int /*<<< orphan*/  MANDOCERR_SPACE_EOL ; 
 int MAN_BLINE ; 
 int MAN_ELINE ; 
 int MAN_NSCOPED ; 
 int MAN_SH ; 
 scalar_t__ ROFFT_BODY ; 
 int ROFF_NONOFILL ; 
 int TOKEN_NONE ; 
 int /*<<< orphan*/  man_breakscope (struct roff_man*,int) ; 
 scalar_t__ man_hasc (char*) ; 
 TYPE_3__* man_macro (int) ; 
 int /*<<< orphan*/  man_unscope (struct roff_man*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mandoc_escape (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mandoc_msg (int /*<<< orphan*/ ,int,int,char*,...) ; 
 int /*<<< orphan*/  roff_body_alloc (struct roff_man*,int,int,int /*<<< orphan*/ ) ; 
 int roffhash_find (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (struct roff_man*,int,int,int,int*,char*) ; 

__attribute__((used)) static int
man_pmacro(struct roff_man *man, int ln, char *buf, int offs)
{
	struct roff_node *n;
	const char	*cp;
	size_t		 sz;
	enum roff_tok	 tok;
	int		 ppos;
	int		 bline;

	/* Determine the line macro. */

	ppos = offs;
	tok = TOKEN_NONE;
	for (sz = 0; sz < 4 && strchr(" \t\\", buf[offs]) == NULL; sz++)
		offs++;
	if (sz > 0 && sz < 4)
		tok = roffhash_find(man->manmac, buf + ppos, sz);
	if (tok == TOKEN_NONE) {
		mandoc_msg(MANDOCERR_MACRO, ln, ppos, "%s", buf + ppos - 1);
		return 1;
	}

	/* Skip a leading escape sequence or tab. */

	switch (buf[offs]) {
	case '\\':
		cp = buf + offs + 1;
		mandoc_escape(&cp, NULL, NULL);
		offs = cp - buf;
		break;
	case '\t':
		offs++;
		break;
	default:
		break;
	}

	/* Jump to the next non-whitespace word. */

	while (buf[offs] == ' ')
		offs++;

	/*
	 * Trailing whitespace.  Note that tabs are allowed to be passed
	 * into the parser as "text", so we only warn about spaces here.
	 */

	if (buf[offs] == '\0' && buf[offs - 1] == ' ')
		mandoc_msg(MANDOCERR_SPACE_EOL, ln, offs - 1, NULL);

	/*
	 * Some macros break next-line scopes; otherwise, remember
	 * whether we are in next-line scope for a block head.
	 */

	man_breakscope(man, tok);
	bline = man->flags & MAN_BLINE;

	/*
	 * If the line in next-line scope ends with \c, keep the
	 * next-line scope open for the subsequent input line.
	 * That is not at all portable, only groff >= 1.22.4
	 * does it, but *if* this weird idiom occurs in a manual
	 * page, that's very likely what the author intended.
	 */

	if (bline && man_hasc(buf + offs))
		bline = 0;

	/* Call to handler... */

	(*man_macro(tok)->fp)(man, tok, ln, ppos, &offs, buf);

	/* In quick mode (for mandocdb), abort after the NAME section. */

	if (man->quick && tok == MAN_SH) {
		n = man->last;
		if (n->type == ROFFT_BODY &&
		    strcmp(n->prev->child->string, "NAME"))
			return 2;
	}

	/*
	 * If we are in a next-line scope for a block head,
	 * close it out now and switch to the body,
	 * unless the next-line scope is allowed to continue.
	 */

	if (bline == 0 ||
	    (man->flags & MAN_BLINE) == 0 ||
	    man->flags & MAN_ELINE ||
	    man_macro(tok)->flags & MAN_NSCOPED)
		return 1;

	man_unscope(man, man->last->parent);
	roff_body_alloc(man, ln, ppos, man->last->tok);
	man->flags &= ~(MAN_BLINE | ROFF_NONOFILL);
	return 1;
}