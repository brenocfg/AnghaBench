#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int sw_t ;
struct TYPE_19__ {scalar_t__ linecount; int /*<<< orphan*/  totalcount; } ;
typedef  TYPE_1__ VI_PRIVATE ;
struct TYPE_22__ {scalar_t__ e_event; char e_c; } ;
struct TYPE_21__ {int /*<<< orphan*/  (* scr_bell ) (TYPE_2__*) ;int /*<<< orphan*/  (* scr_refresh ) (TYPE_2__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* scr_clrtoeol ) (TYPE_2__*) ;int /*<<< orphan*/  (* scr_addstr ) (TYPE_2__*,char const*,size_t) ;int /*<<< orphan*/  (* scr_move ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_20__ {TYPE_3__* gp; } ;
typedef  TYPE_2__ SCR ;
typedef  TYPE_3__ GS ;
typedef  TYPE_4__ EVENT ;

/* Variables and functions */
 char CH_QUIT ; 
 int /*<<< orphan*/  CMSG_CONT ; 
 int /*<<< orphan*/  CMSG_CONT_EX ; 
 int /*<<< orphan*/  CMSG_CONT_Q ; 
 int /*<<< orphan*/  CMSG_CONT_S ; 
 scalar_t__ E_CHARACTER ; 
 scalar_t__ E_INTERRUPT ; 
 int /*<<< orphan*/  F_SET (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_INTERRUPTED ; 
 scalar_t__ IS_ONELINE (TYPE_2__*) ; 
 int /*<<< orphan*/  LASTLINE (TYPE_2__*) ; 
#define  SCROLL_W 130 
#define  SCROLL_W_EX 129 
#define  SCROLL_W_QUIT 128 
 TYPE_1__* VIP (TYPE_2__*) ; 
 int /*<<< orphan*/  abort () ; 
 char* msg_cmsg (TYPE_2__*,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,char const*,size_t) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub4 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (TYPE_2__*) ; 
 scalar_t__ v_event_get (TYPE_2__*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vs_wait(SCR *sp, int *continuep, sw_t wtype)
{
	EVENT ev;
	VI_PRIVATE *vip;
	const char *p;
	GS *gp;
	size_t len;

	gp = sp->gp;
	vip = VIP(sp);

	(void)gp->scr_move(sp, LASTLINE(sp), 0);
	if (IS_ONELINE(sp))
		p = msg_cmsg(sp, CMSG_CONT_S, &len);
	else
		switch (wtype) {
		case SCROLL_W_QUIT:
			p = msg_cmsg(sp, CMSG_CONT_Q, &len);
			break;
		case SCROLL_W_EX:
			p = msg_cmsg(sp, CMSG_CONT_EX, &len);
			break;
		case SCROLL_W:
			p = msg_cmsg(sp, CMSG_CONT, &len);
			break;
		default:
			abort();
			/* NOTREACHED */
		}
	(void)gp->scr_addstr(sp, p, len);

	++vip->totalcount;
	vip->linecount = 0;

	(void)gp->scr_clrtoeol(sp);
	(void)gp->scr_refresh(sp, 0);

	/* Get a single character from the terminal. */
	if (continuep != NULL)
		*continuep = 0;
	for (;;) {
		if (v_event_get(sp, &ev, 0, 0))
			return;
		if (ev.e_event == E_CHARACTER)
			break;
		if (ev.e_event == E_INTERRUPT) {
			ev.e_c = CH_QUIT;
			F_SET(gp, G_INTERRUPTED);
			break;
		}
		(void)gp->scr_bell(sp);
	}
	switch (wtype) {
	case SCROLL_W_QUIT:
		if (ev.e_c == CH_QUIT)
			F_SET(gp, G_INTERRUPTED);
		break;
	case SCROLL_W_EX:
		if (ev.e_c == ':' && continuep != NULL)
			*continuep = 1;
		break;
	case SCROLL_W:
		break;
	}
}