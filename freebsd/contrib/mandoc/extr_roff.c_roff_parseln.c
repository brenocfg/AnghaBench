#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct roff {TYPE_4__* man; int /*<<< orphan*/ * tbl; TYPE_2__* last; int /*<<< orphan*/ * eqn; int /*<<< orphan*/  escape; scalar_t__ eqn_inline; TYPE_1__* last_eqn; } ;
struct buf {char* buf; } ;
typedef  enum roff_tok { ____Placeholder_roff_tok } roff_tok ;
struct TYPE_8__ {int /*<<< orphan*/  next; int /*<<< orphan*/ * last; } ;
struct TYPE_7__ {int (* text ) (struct roff*,int,struct buf*,int,int,int,int*) ;int (* sub ) (struct roff*,int,struct buf*,int,int,int,int*) ;int (* proc ) (struct roff*,int,struct buf*,int,int,int,int*) ;} ;
struct TYPE_6__ {int tok; } ;
struct TYPE_5__ {scalar_t__ delim; } ;

/* Variables and functions */
 int /*<<< orphan*/  MANDOCERR_COMMENT_BAD ; 
 int /*<<< orphan*/  MANDOCERR_TBLMACRO ; 
 int ROFF_CONT ; 
 int ROFF_Dd ; 
 int ROFF_EQ ; 
 int ROFF_IGN ; 
 int ROFF_MASK ; 
 int /*<<< orphan*/  ROFF_NEXT_SIBLING ; 
 int ROFF_REPARSE ; 
 int ROFF_TH ; 
 int ROFF_TS ; 
 int ROFF_br ; 
 int ROFF_ce ; 
 int ROFF_rj ; 
 int ROFF_sp ; 
 int TOKEN_NONE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  eqn_read (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mandoc_msg (int /*<<< orphan*/ ,int,int,char*,...) ; 
 int /*<<< orphan*/  roff_addtbl (TYPE_4__*,int,int /*<<< orphan*/ *) ; 
 int roff_eqndelim (struct roff*,struct buf*,int) ; 
 int roff_expand (struct roff*,struct buf*,int,int,int /*<<< orphan*/ ) ; 
 int roff_getcontrol (struct roff*,char*,int*) ; 
 int roff_parse (struct roff*,char*,int*,int,int) ; 
 int roff_parsetext (struct roff*,struct buf*,int,int*) ; 
 scalar_t__ roffce_lines ; 
 int /*<<< orphan*/ * roffce_node ; 
 TYPE_3__* roffs ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int stub1 (struct roff*,int,struct buf*,int,int,int,int*) ; 
 int stub2 (struct roff*,int,struct buf*,int,int,int,int*) ; 
 int stub3 (struct roff*,int,struct buf*,int,int,int,int*) ; 
 int /*<<< orphan*/  tbl_read (int /*<<< orphan*/ *,int,char*,int) ; 

int
roff_parseln(struct roff *r, int ln, struct buf *buf, int *offs)
{
	enum roff_tok	 t;
	int		 e;
	int		 pos;	/* parse point */
	int		 spos;	/* saved parse point for messages */
	int		 ppos;	/* original offset in buf->buf */
	int		 ctl;	/* macro line (boolean) */

	ppos = pos = *offs;

	/* Handle in-line equation delimiters. */

	if (r->tbl == NULL &&
	    r->last_eqn != NULL && r->last_eqn->delim &&
	    (r->eqn == NULL || r->eqn_inline)) {
		e = roff_eqndelim(r, buf, pos);
		if (e == ROFF_REPARSE)
			return e;
		assert(e == ROFF_CONT);
	}

	/* Expand some escape sequences. */

	e = roff_expand(r, buf, ln, pos, r->escape);
	if ((e & ROFF_MASK) == ROFF_IGN)
		return e;
	assert(e == ROFF_CONT);

	ctl = roff_getcontrol(r, buf->buf, &pos);

	/*
	 * First, if a scope is open and we're not a macro, pass the
	 * text through the macro's filter.
	 * Equations process all content themselves.
	 * Tables process almost all content themselves, but we want
	 * to warn about macros before passing it there.
	 */

	if (r->last != NULL && ! ctl) {
		t = r->last->tok;
		e = (*roffs[t].text)(r, t, buf, ln, pos, pos, offs);
		if ((e & ROFF_MASK) == ROFF_IGN)
			return e;
		e &= ~ROFF_MASK;
	} else
		e = ROFF_IGN;
	if (r->eqn != NULL && strncmp(buf->buf + ppos, ".EN", 3)) {
		eqn_read(r->eqn, buf->buf + ppos);
		return e;
	}
	if (r->tbl != NULL && (ctl == 0 || buf->buf[pos] == '\0')) {
		tbl_read(r->tbl, ln, buf->buf, ppos);
		roff_addtbl(r->man, ln, r->tbl);
		return e;
	}
	if ( ! ctl)
		return roff_parsetext(r, buf, pos, offs) | e;

	/* Skip empty request lines. */

	if (buf->buf[pos] == '"') {
		mandoc_msg(MANDOCERR_COMMENT_BAD, ln, pos, NULL);
		return ROFF_IGN;
	} else if (buf->buf[pos] == '\0')
		return ROFF_IGN;

	/*
	 * If a scope is open, go to the child handler for that macro,
	 * as it may want to preprocess before doing anything with it.
	 * Don't do so if an equation is open.
	 */

	if (r->last) {
		t = r->last->tok;
		return (*roffs[t].sub)(r, t, buf, ln, ppos, pos, offs);
	}

	/* No scope is open.  This is a new request or macro. */

	spos = pos;
	t = roff_parse(r, buf->buf, &pos, ln, ppos);

	/* Tables ignore most macros. */

	if (r->tbl != NULL && (t == TOKEN_NONE || t == ROFF_TS ||
	    t == ROFF_br || t == ROFF_ce || t == ROFF_rj || t == ROFF_sp)) {
		mandoc_msg(MANDOCERR_TBLMACRO,
		    ln, pos, "%s", buf->buf + spos);
		if (t != TOKEN_NONE)
			return ROFF_IGN;
		while (buf->buf[pos] != '\0' && buf->buf[pos] != ' ')
			pos++;
		while (buf->buf[pos] == ' ')
			pos++;
		tbl_read(r->tbl, ln, buf->buf, pos);
		roff_addtbl(r->man, ln, r->tbl);
		return ROFF_IGN;
	}

	/* For now, let high level macros abort .ce mode. */

	if (ctl && roffce_node != NULL &&
	    (t == TOKEN_NONE || t == ROFF_Dd || t == ROFF_EQ ||
	     t == ROFF_TH || t == ROFF_TS)) {
		r->man->last = roffce_node;
		r->man->next = ROFF_NEXT_SIBLING;
		roffce_lines = 0;
		roffce_node = NULL;
	}

	/*
	 * This is neither a roff request nor a user-defined macro.
	 * Let the standard macro set parsers handle it.
	 */

	if (t == TOKEN_NONE)
		return ROFF_CONT;

	/* Execute a roff request or a user defined macro. */

	return (*roffs[t].proc)(r, t, buf, ln, spos, pos, offs);
}