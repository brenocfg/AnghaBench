#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_12__ {int /*<<< orphan*/  e_ch; int /*<<< orphan*/  e_c; int /*<<< orphan*/  e_value; int /*<<< orphan*/  e_event; } ;
struct TYPE_11__ {size_t i_next; size_t i_cnt; size_t i_nelem; TYPE_3__* i_event; } ;
struct TYPE_10__ {TYPE_2__* gp; } ;
typedef  TYPE_1__ SCR ;
typedef  TYPE_2__ GS ;
typedef  TYPE_3__ EVENT ;
typedef  int /*<<< orphan*/  CHAR_T ;

/* Variables and functions */
 int /*<<< orphan*/  BCOPY (TYPE_3__*,TYPE_3__*,size_t) ; 
 int /*<<< orphan*/  E_CHARACTER ; 
 int /*<<< orphan*/  F_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KEY_VAL (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX (size_t,int) ; 
 size_t TERM_PUSH_SHIFT ; 
 scalar_t__ v_event_grow (TYPE_1__*,int /*<<< orphan*/ ) ; 

int
v_event_push(
	SCR *sp,
	EVENT *p_evp,			/* Push event. */
	CHAR_T *p_s,			/* Push characters. */
	size_t nitems,			/* Number of items to push. */
	u_int flags)			/* CH_* flags. */
{
	EVENT *evp;
	GS *gp;
	size_t total;

	/* If we have room, stuff the items into the buffer. */
	gp = sp->gp;
	if (nitems <= gp->i_next ||
	    (gp->i_event != NULL && gp->i_cnt == 0 && nitems <= gp->i_nelem)) {
		if (gp->i_cnt != 0)
			gp->i_next -= nitems;
		goto copy;
	}

	/*
	 * If there are currently items in the queue, shift them up,
	 * leaving some extra room.  Get enough space plus a little
	 * extra.
	 */
#define	TERM_PUSH_SHIFT	30
	total = gp->i_cnt + gp->i_next + nitems + TERM_PUSH_SHIFT;
	if (total >= gp->i_nelem && v_event_grow(sp, MAX(total, 64)))
		return (1);
	if (gp->i_cnt)
		BCOPY(gp->i_event + gp->i_next,
		    gp->i_event + TERM_PUSH_SHIFT + nitems, gp->i_cnt);
	gp->i_next = TERM_PUSH_SHIFT;

	/* Put the new items into the queue. */
copy:	gp->i_cnt += nitems;
	for (evp = gp->i_event + gp->i_next; nitems--; ++evp) {
		if (p_evp != NULL)
			*evp = *p_evp++;
		else {
			evp->e_event = E_CHARACTER;
			evp->e_c = *p_s++;
			evp->e_value = KEY_VAL(sp, evp->e_c);
			F_INIT(&evp->e_ch, flags);
		}
	}
	return (0);
}