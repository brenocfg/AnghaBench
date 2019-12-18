#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct eqn_node {char* data; char* start; char* end; char const* toksz; int gsize; TYPE_1__* node; } ;
struct eqn_box {void* type; char* text; int expectargs; int args; int size; struct eqn_box* parent; struct eqn_box* prev; struct eqn_box* last; struct eqn_box* first; struct eqn_box* next; void* font; int /*<<< orphan*/ * left; void* right; int /*<<< orphan*/  pos; void* top; void* bottom; } ;
typedef  enum eqn_tok { ____Placeholder_eqn_tok } eqn_tok ;
struct TYPE_2__ {int /*<<< orphan*/  pos; int /*<<< orphan*/  line; struct eqn_box* eqn; } ;

/* Variables and functions */
 void* EQNFONT_BOLD ; 
 void* EQNFONT_FAT ; 
 void* EQNFONT_ITALIC ; 
 void* EQNFONT_NONE ; 
 void* EQNFONT_ROMAN ; 
 int /*<<< orphan*/  EQNPOS_FROM ; 
 int /*<<< orphan*/  EQNPOS_FROMTO ; 
 int /*<<< orphan*/  EQNPOS_OVER ; 
 int /*<<< orphan*/  EQNPOS_SQRT ; 
 int /*<<< orphan*/  EQNPOS_SUB ; 
 int /*<<< orphan*/  EQNPOS_SUBSUP ; 
 int /*<<< orphan*/  EQNPOS_SUP ; 
 int /*<<< orphan*/  EQNPOS_TO ; 
 void* EQN_LIST ; 
 void* EQN_MATRIX ; 
 void* EQN_PILE ; 
 void* EQN_SUBEXPR ; 
 void* EQN_TEXT ; 
#define  EQN_TOK_ABOVE 177 
#define  EQN_TOK_BACK 176 
#define  EQN_TOK_BAR 175 
#define  EQN_TOK_BOLD 174 
#define  EQN_TOK_BRACE_CLOSE 173 
#define  EQN_TOK_BRACE_OPEN 172 
#define  EQN_TOK_CCOL 171 
#define  EQN_TOK_CPILE 170 
#define  EQN_TOK_DEFINE 169 
#define  EQN_TOK_DELIM 168 
#define  EQN_TOK_DOT 167 
#define  EQN_TOK_DOTDOT 166 
#define  EQN_TOK_DOWN 165 
#define  EQN_TOK_DYAD 164 
#define  EQN_TOK_EOF 163 
#define  EQN_TOK_FAT 162 
#define  EQN_TOK_FROM 161 
#define  EQN_TOK_FUNC 160 
#define  EQN_TOK_FWD 159 
#define  EQN_TOK_GFONT 158 
#define  EQN_TOK_GSIZE 157 
#define  EQN_TOK_HAT 156 
#define  EQN_TOK_ITALIC 155 
#define  EQN_TOK_LCOL 154 
#define  EQN_TOK_LEFT 153 
#define  EQN_TOK_LINEUP 152 
#define  EQN_TOK_LPILE 151 
#define  EQN_TOK_MARK 150 
#define  EQN_TOK_MATRIX 149 
#define  EQN_TOK_NDEFINE 148 
#define  EQN_TOK_OVER 147 
#define  EQN_TOK_PILE 146 
#define  EQN_TOK_QUOTED 145 
#define  EQN_TOK_RCOL 144 
#define  EQN_TOK_RIGHT 143 
#define  EQN_TOK_ROMAN 142 
#define  EQN_TOK_RPILE 141 
#define  EQN_TOK_SIZE 140 
#define  EQN_TOK_SQRT 139 
#define  EQN_TOK_SUB 138 
#define  EQN_TOK_SUP 137 
#define  EQN_TOK_SYM 136 
#define  EQN_TOK_TDEFINE 135 
#define  EQN_TOK_TILDE 134 
#define  EQN_TOK_TO 133 
#define  EQN_TOK_UNDEF 132 
#define  EQN_TOK_UNDER 131 
#define  EQN_TOK_UP 130 
#define  EQN_TOK_VEC 129 
#define  EQN_TOK__MAX 128 
 int /*<<< orphan*/  MANDOCERR_BLK_NOTOPEN ; 
 int /*<<< orphan*/  MANDOCERR_EQN_NOBOX ; 
 int /*<<< orphan*/  MANDOCERR_IT_NONUM ; 
 int /*<<< orphan*/  MANDOCERR_IT_STRAY ; 
 int /*<<< orphan*/  MANDOCERR_REQ_EMPTY ; 
 int /*<<< orphan*/  MODE_NOSUB ; 
 int /*<<< orphan*/  MODE_QUOTED ; 
 int /*<<< orphan*/  MODE_SUB ; 
 int /*<<< orphan*/  MODE_TOK ; 
 int /*<<< orphan*/  STRNEQ (char*,char const*,char*,int) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 struct eqn_box* eqn_box_alloc (struct eqn_node*,struct eqn_box*) ; 
 struct eqn_box* eqn_box_makebinary (struct eqn_node*,struct eqn_box*) ; 
 int /*<<< orphan*/  eqn_def (struct eqn_node*) ; 
 int /*<<< orphan*/  eqn_delim (struct eqn_node*) ; 
 int eqn_next (struct eqn_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * eqn_toks ; 
 int /*<<< orphan*/  eqn_undef (struct eqn_node*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  isalpha (unsigned char) ; 
 int /*<<< orphan*/  isdigit (unsigned char) ; 
 int /*<<< orphan*/  mandoc_escape (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mandoc_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 void* mandoc_strdup (char const*) ; 
 void* mandoc_strndup (char*,char const*) ; 
 int mandoc_strntoi (char*,char const*,int) ; 
 int strspn (char*,char*) ; 

void
eqn_parse(struct eqn_node *ep)
{
	struct eqn_box	*cur, *nbox, *parent, *split;
	const char	*cp, *cpn;
	char		*p;
	enum eqn_tok	 tok;
	enum { CCL_LET, CCL_DIG, CCL_PUN } ccl, ccln;
	int		 size;

	parent = ep->node->eqn;
	assert(parent != NULL);

	/*
	 * Empty equation.
	 * Do not add it to the high-level syntax tree.
	 */

	if (ep->data == NULL)
		return;

	ep->start = ep->end = ep->data + strspn(ep->data, " ^~");

next_tok:
	tok = eqn_next(ep, MODE_TOK);
	switch (tok) {
	case EQN_TOK_UNDEF:
		eqn_undef(ep);
		break;
	case EQN_TOK_NDEFINE:
	case EQN_TOK_DEFINE:
		eqn_def(ep);
		break;
	case EQN_TOK_TDEFINE:
		if (eqn_next(ep, MODE_NOSUB) == EQN_TOK_EOF ||
		    eqn_next(ep, MODE_QUOTED) == EQN_TOK_EOF)
			mandoc_msg(MANDOCERR_REQ_EMPTY,
			    ep->node->line, ep->node->pos, "tdefine");
		break;
	case EQN_TOK_DELIM:
		eqn_delim(ep);
		break;
	case EQN_TOK_GFONT:
		if (eqn_next(ep, MODE_SUB) == EQN_TOK_EOF)
			mandoc_msg(MANDOCERR_REQ_EMPTY, ep->node->line,
			    ep->node->pos, "%s", eqn_toks[tok]);
		break;
	case EQN_TOK_MARK:
	case EQN_TOK_LINEUP:
		/* Ignore these. */
		break;
	case EQN_TOK_DYAD:
	case EQN_TOK_VEC:
	case EQN_TOK_UNDER:
	case EQN_TOK_BAR:
	case EQN_TOK_TILDE:
	case EQN_TOK_HAT:
	case EQN_TOK_DOT:
	case EQN_TOK_DOTDOT:
		if (parent->last == NULL) {
			mandoc_msg(MANDOCERR_EQN_NOBOX, ep->node->line,
			    ep->node->pos, "%s", eqn_toks[tok]);
			cur = eqn_box_alloc(ep, parent);
			cur->type = EQN_TEXT;
			cur->text = mandoc_strdup("");
		}
		parent = eqn_box_makebinary(ep, parent);
		parent->type = EQN_LIST;
		parent->expectargs = 1;
		parent->font = EQNFONT_ROMAN;
		switch (tok) {
		case EQN_TOK_DOTDOT:
			parent->top = mandoc_strdup("\\[ad]");
			break;
		case EQN_TOK_VEC:
			parent->top = mandoc_strdup("\\[->]");
			break;
		case EQN_TOK_DYAD:
			parent->top = mandoc_strdup("\\[<>]");
			break;
		case EQN_TOK_TILDE:
			parent->top = mandoc_strdup("\\[a~]");
			break;
		case EQN_TOK_UNDER:
			parent->bottom = mandoc_strdup("\\[ul]");
			break;
		case EQN_TOK_BAR:
			parent->top = mandoc_strdup("\\[rn]");
			break;
		case EQN_TOK_DOT:
			parent->top = mandoc_strdup("\\[a.]");
			break;
		case EQN_TOK_HAT:
			parent->top = mandoc_strdup("\\[ha]");
			break;
		default:
			abort();
		}
		parent = parent->parent;
		break;
	case EQN_TOK_FWD:
	case EQN_TOK_BACK:
	case EQN_TOK_DOWN:
	case EQN_TOK_UP:
		if (eqn_next(ep, MODE_SUB) == EQN_TOK_EOF)
			mandoc_msg(MANDOCERR_REQ_EMPTY, ep->node->line,
			    ep->node->pos, "%s", eqn_toks[tok]);
		break;
	case EQN_TOK_FAT:
	case EQN_TOK_ROMAN:
	case EQN_TOK_ITALIC:
	case EQN_TOK_BOLD:
		while (parent->args == parent->expectargs)
			parent = parent->parent;
		/*
		 * These values apply to the next word or sequence of
		 * words; thus, we mark that we'll have a child with
		 * exactly one of those.
		 */
		parent = eqn_box_alloc(ep, parent);
		parent->type = EQN_LIST;
		parent->expectargs = 1;
		switch (tok) {
		case EQN_TOK_FAT:
			parent->font = EQNFONT_FAT;
			break;
		case EQN_TOK_ROMAN:
			parent->font = EQNFONT_ROMAN;
			break;
		case EQN_TOK_ITALIC:
			parent->font = EQNFONT_ITALIC;
			break;
		case EQN_TOK_BOLD:
			parent->font = EQNFONT_BOLD;
			break;
		default:
			abort();
		}
		break;
	case EQN_TOK_SIZE:
	case EQN_TOK_GSIZE:
		/* Accept two values: integral size and a single. */
		if (eqn_next(ep, MODE_SUB) == EQN_TOK_EOF) {
			mandoc_msg(MANDOCERR_REQ_EMPTY, ep->node->line,
			    ep->node->pos, "%s", eqn_toks[tok]);
			break;
		}
		size = mandoc_strntoi(ep->start, ep->toksz, 10);
		if (-1 == size) {
			mandoc_msg(MANDOCERR_IT_NONUM, ep->node->line,
			    ep->node->pos, "%s", eqn_toks[tok]);
			break;
		}
		if (EQN_TOK_GSIZE == tok) {
			ep->gsize = size;
			break;
		}
		while (parent->args == parent->expectargs)
			parent = parent->parent;
		parent = eqn_box_alloc(ep, parent);
		parent->type = EQN_LIST;
		parent->expectargs = 1;
		parent->size = size;
		break;
	case EQN_TOK_FROM:
	case EQN_TOK_TO:
	case EQN_TOK_SUB:
	case EQN_TOK_SUP:
		/*
		 * We have a left-right-associative expression.
		 * Repivot under a positional node, open a child scope
		 * and keep on reading.
		 */
		if (parent->last == NULL) {
			mandoc_msg(MANDOCERR_EQN_NOBOX, ep->node->line,
			    ep->node->pos, "%s", eqn_toks[tok]);
			cur = eqn_box_alloc(ep, parent);
			cur->type = EQN_TEXT;
			cur->text = mandoc_strdup("");
		}
		while (parent->expectargs == 1 && parent->args == 1)
			parent = parent->parent;
		if (tok == EQN_TOK_FROM || tok == EQN_TOK_TO)  {
			for (cur = parent; cur != NULL; cur = cur->parent)
				if (cur->pos == EQNPOS_SUB ||
				    cur->pos == EQNPOS_SUP ||
				    cur->pos == EQNPOS_SUBSUP ||
				    cur->pos == EQNPOS_SQRT ||
				    cur->pos == EQNPOS_OVER)
					break;
			if (cur != NULL)
				parent = cur->parent;
		}
		if (tok == EQN_TOK_SUP && parent->pos == EQNPOS_SUB) {
			parent->expectargs = 3;
			parent->pos = EQNPOS_SUBSUP;
			break;
		}
		if (tok == EQN_TOK_TO && parent->pos == EQNPOS_FROM) {
			parent->expectargs = 3;
			parent->pos = EQNPOS_FROMTO;
			break;
		}
		parent = eqn_box_makebinary(ep, parent);
		switch (tok) {
		case EQN_TOK_FROM:
			parent->pos = EQNPOS_FROM;
			break;
		case EQN_TOK_TO:
			parent->pos = EQNPOS_TO;
			break;
		case EQN_TOK_SUP:
			parent->pos = EQNPOS_SUP;
			break;
		case EQN_TOK_SUB:
			parent->pos = EQNPOS_SUB;
			break;
		default:
			abort();
		}
		break;
	case EQN_TOK_SQRT:
		while (parent->args == parent->expectargs)
			parent = parent->parent;
		/*
		 * Accept a left-right-associative set of arguments just
		 * like sub and sup and friends but without rebalancing
		 * under a pivot.
		 */
		parent = eqn_box_alloc(ep, parent);
		parent->type = EQN_SUBEXPR;
		parent->pos = EQNPOS_SQRT;
		parent->expectargs = 1;
		break;
	case EQN_TOK_OVER:
		/*
		 * We have a right-left-associative fraction.
		 * Close out anything that's currently open, then
		 * rebalance and continue reading.
		 */
		if (parent->last == NULL) {
			mandoc_msg(MANDOCERR_EQN_NOBOX, ep->node->line,
			    ep->node->pos, "%s", eqn_toks[tok]);
			cur = eqn_box_alloc(ep, parent);
			cur->type = EQN_TEXT;
			cur->text = mandoc_strdup("");
		}
		while (parent->args == parent->expectargs)
			parent = parent->parent;
		while (EQN_SUBEXPR == parent->type)
			parent = parent->parent;
		parent = eqn_box_makebinary(ep, parent);
		parent->pos = EQNPOS_OVER;
		break;
	case EQN_TOK_RIGHT:
	case EQN_TOK_BRACE_CLOSE:
		/*
		 * Close out the existing brace.
		 * FIXME: this is a shitty sentinel: we should really
		 * have a native EQN_BRACE type or whatnot.
		 */
		for (cur = parent; cur != NULL; cur = cur->parent)
			if (cur->type == EQN_LIST &&
			    cur->expectargs > 1 &&
			    (tok == EQN_TOK_BRACE_CLOSE ||
			     cur->left != NULL))
				break;
		if (cur == NULL) {
			mandoc_msg(MANDOCERR_BLK_NOTOPEN, ep->node->line,
			    ep->node->pos, "%s", eqn_toks[tok]);
			break;
		}
		parent = cur;
		if (EQN_TOK_RIGHT == tok) {
			if (eqn_next(ep, MODE_SUB) == EQN_TOK_EOF) {
				mandoc_msg(MANDOCERR_REQ_EMPTY,
				    ep->node->line, ep->node->pos,
				    "%s", eqn_toks[tok]);
				break;
			}
			/* Handling depends on right/left. */
			if (STRNEQ(ep->start, ep->toksz, "ceiling", 7))
				parent->right = mandoc_strdup("\\[rc]");
			else if (STRNEQ(ep->start, ep->toksz, "floor", 5))
				parent->right = mandoc_strdup("\\[rf]");
			else
				parent->right =
				    mandoc_strndup(ep->start, ep->toksz);
		}
		parent = parent->parent;
		if (tok == EQN_TOK_BRACE_CLOSE &&
		    (parent->type == EQN_PILE ||
		     parent->type == EQN_MATRIX))
			parent = parent->parent;
		/* Close out any "singleton" lists. */
		while (parent->type == EQN_LIST &&
		    parent->expectargs == 1 &&
		    parent->args == 1)
			parent = parent->parent;
		break;
	case EQN_TOK_BRACE_OPEN:
	case EQN_TOK_LEFT:
		/*
		 * If we already have something in the stack and we're
		 * in an expression, then rewind til we're not any more
		 * (just like with the text node).
		 */
		while (parent->args == parent->expectargs)
			parent = parent->parent;
		if (EQN_TOK_LEFT == tok &&
		    eqn_next(ep, MODE_SUB) == EQN_TOK_EOF) {
			mandoc_msg(MANDOCERR_REQ_EMPTY, ep->node->line,
			    ep->node->pos, "%s", eqn_toks[tok]);
			break;
		}
		parent = eqn_box_alloc(ep, parent);
		parent->type = EQN_LIST;
		if (EQN_TOK_LEFT == tok) {
			if (STRNEQ(ep->start, ep->toksz, "ceiling", 7))
				parent->left = mandoc_strdup("\\[lc]");
			else if (STRNEQ(ep->start, ep->toksz, "floor", 5))
				parent->left = mandoc_strdup("\\[lf]");
			else
				parent->left =
				    mandoc_strndup(ep->start, ep->toksz);
		}
		break;
	case EQN_TOK_PILE:
	case EQN_TOK_LPILE:
	case EQN_TOK_RPILE:
	case EQN_TOK_CPILE:
	case EQN_TOK_CCOL:
	case EQN_TOK_LCOL:
	case EQN_TOK_RCOL:
		while (parent->args == parent->expectargs)
			parent = parent->parent;
		parent = eqn_box_alloc(ep, parent);
		parent->type = EQN_PILE;
		parent->expectargs = 1;
		break;
	case EQN_TOK_ABOVE:
		for (cur = parent; cur != NULL; cur = cur->parent)
			if (cur->type == EQN_PILE)
				break;
		if (cur == NULL) {
			mandoc_msg(MANDOCERR_IT_STRAY, ep->node->line,
			    ep->node->pos, "%s", eqn_toks[tok]);
			break;
		}
		parent = eqn_box_alloc(ep, cur);
		parent->type = EQN_LIST;
		break;
	case EQN_TOK_MATRIX:
		while (parent->args == parent->expectargs)
			parent = parent->parent;
		parent = eqn_box_alloc(ep, parent);
		parent->type = EQN_MATRIX;
		parent->expectargs = 1;
		break;
	case EQN_TOK_EOF:
		return;
	case EQN_TOK__MAX:
	case EQN_TOK_FUNC:
	case EQN_TOK_QUOTED:
	case EQN_TOK_SYM:
		p = ep->start;
		assert(p != NULL);
		/*
		 * If we already have something in the stack and we're
		 * in an expression, then rewind til we're not any more.
		 */
		while (parent->args == parent->expectargs)
			parent = parent->parent;
		cur = eqn_box_alloc(ep, parent);
		cur->type = EQN_TEXT;
		cur->text = p;
		switch (tok) {
		case EQN_TOK_FUNC:
			cur->font = EQNFONT_ROMAN;
			break;
		case EQN_TOK_QUOTED:
			if (cur->font == EQNFONT_NONE)
				cur->font = EQNFONT_ITALIC;
			break;
		case EQN_TOK_SYM:
			break;
		default:
			if (cur->font != EQNFONT_NONE || *p == '\0')
				break;
			cpn = p - 1;
			ccln = CCL_LET;
			split = NULL;
			for (;;) {
				/* Advance to next character. */
				cp = cpn++;
				ccl = ccln;
				ccln = isalpha((unsigned char)*cpn) ? CCL_LET :
				    isdigit((unsigned char)*cpn) ||
				    (*cpn == '.' && (ccl == CCL_DIG ||
				     isdigit((unsigned char)cpn[1]))) ?
				    CCL_DIG : CCL_PUN;
				/* No boundary before first character. */
				if (cp < p)
					continue;
				cur->font = ccl == CCL_LET ?
				    EQNFONT_ITALIC : EQNFONT_ROMAN;
				if (*cp == '\\')
					mandoc_escape(&cpn, NULL, NULL);
				/* No boundary after last character. */
				if (*cpn == '\0')
					break;
				if (ccln == ccl && *cp != ',' && *cpn != ',')
					continue;
				/* Boundary found, split the text. */
				if (parent->args == parent->expectargs) {
					/* Remove the text from the tree. */
					if (cur->prev == NULL)
						parent->first = cur->next;
					else
						cur->prev->next = NULL;
					parent->last = cur->prev;
					parent->args--;
					/* Set up a list instead. */
					split = eqn_box_alloc(ep, parent);
					split->type = EQN_LIST;
					/* Insert the word into the list. */
					split->first = split->last = cur;
					cur->parent = split;
					cur->prev = NULL;
					parent = split;
				}
				/* Append a new text box. */
				nbox = eqn_box_alloc(ep, parent);
				nbox->type = EQN_TEXT;
				nbox->text = mandoc_strdup(cpn);
				/* Truncate the old box. */
				p = mandoc_strndup(cur->text,
				    cpn - cur->text);
				free(cur->text);
				cur->text = p;
				/* Setup to process the new box. */
				cur = nbox;
				p = nbox->text;
				cpn = p - 1;
				ccln = CCL_LET;
			}
			if (split != NULL)
				parent = split->parent;
			break;
		}
		break;
	default:
		abort();
	}
	goto next_tok;
}