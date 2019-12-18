#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ e_event; int e_len; scalar_t__ e_flags; int /*<<< orphan*/  e_c; int /*<<< orphan*/  e_value; int /*<<< orphan*/ * e_csp; } ;
struct TYPE_9__ {size_t i_nelem; size_t i_next; size_t i_cnt; TYPE_3__* i_event; } ;
struct TYPE_8__ {TYPE_2__* gp; } ;
typedef  TYPE_1__ SCR ;
typedef  TYPE_2__ GS ;
typedef  TYPE_3__ EVENT ;
typedef  int /*<<< orphan*/  CHAR_T ;

/* Variables and functions */
 scalar_t__ E_CHARACTER ; 
 scalar_t__ E_STRING ; 
 int /*<<< orphan*/  KEY_VAL (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX (size_t,int) ; 
 int /*<<< orphan*/  v_event_grow (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
v_event_append(
	SCR *sp,
	EVENT *argp)
{
	CHAR_T *s;			/* Characters. */
	EVENT *evp;
	GS *gp;
	size_t nevents;			/* Number of events. */

	/* Grow the buffer as necessary. */
	nevents = argp->e_event == E_STRING ? argp->e_len : 1;
	gp = sp->gp;
	if (gp->i_event == NULL ||
	    nevents > gp->i_nelem - (gp->i_next + gp->i_cnt))
		v_event_grow(sp, MAX(nevents, 64));
	evp = gp->i_event + gp->i_next + gp->i_cnt;
	gp->i_cnt += nevents;

	/* Transform strings of characters into single events. */
	if (argp->e_event == E_STRING)
		for (s = argp->e_csp; nevents--; ++evp) {
			evp->e_event = E_CHARACTER;
			evp->e_c = *s++;
			evp->e_value = KEY_VAL(sp, evp->e_c);
			evp->e_flags = 0;
		}
	else
		*evp = *argp;
	return (0);
}