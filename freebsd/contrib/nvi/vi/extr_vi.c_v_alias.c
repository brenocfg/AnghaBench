#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VIKEYS ;
struct TYPE_3__ {int key; } ;
typedef  TYPE_1__ VICMD ;
typedef  int /*<<< orphan*/  SCR ;
typedef  char CHAR_T ;

/* Variables and functions */
 int CH_NOMAP ; 
 int CH_QUOTED ; 
 scalar_t__ v_event_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  const* vikeys ; 

__attribute__((used)) static VIKEYS const *
v_alias(
	SCR *sp,
	VICMD *vp,
	VIKEYS const *kp)
{
	CHAR_T push;

	switch (vp->key) {
	case 'C':			/* C -> c$ */
		push = '$';
		vp->key = 'c';
		break;
	case 'D':			/* D -> d$ */
		push = '$';
		vp->key = 'd';
		break;
	case 'S':			/* S -> c_ */
		push = '_';
		vp->key = 'c';
		break;
	case 'Y':			/* Y -> y_ */
		push = '_';
		vp->key = 'y';
		break;
	default:
		return (kp);
	}
	return (v_event_push(sp,
	    NULL, &push, 1, CH_NOMAP | CH_QUOTED) ? NULL : &vikeys[vp->key]);
}