#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int scr_keyval_t ;
struct TYPE_4__ {int /*<<< orphan*/ * c_cc; } ;
struct TYPE_5__ {TYPE_1__ orig; } ;
typedef  int /*<<< orphan*/  SCR ;
typedef  TYPE_2__ CL_PRIVATE ;
typedef  int /*<<< orphan*/  CHAR_T ;

/* Variables and functions */
 TYPE_2__* CLP (int /*<<< orphan*/ *) ; 
#define  KEY_VEOF 131 
#define  KEY_VERASE 130 
#define  KEY_VKILL 129 
#define  KEY_VWERASE 128 
 size_t VEOF ; 
 size_t VERASE ; 
 size_t VKILL ; 
 size_t VWERASE ; 
 int /*<<< orphan*/  _POSIX_VDISABLE ; 

int
cl_keyval(SCR *sp, scr_keyval_t val, CHAR_T *chp, int *dnep)
{
	CL_PRIVATE *clp;

	/*
	 * VEOF, VERASE and VKILL are required by POSIX 1003.1-1990,
	 * VWERASE is a 4BSD extension.
	 */
	clp = CLP(sp);
	switch (val) {
	case KEY_VEOF:
		*dnep = (*chp = clp->orig.c_cc[VEOF]) == _POSIX_VDISABLE;
		break;
	case KEY_VERASE:
		*dnep = (*chp = clp->orig.c_cc[VERASE]) == _POSIX_VDISABLE;
		break;
	case KEY_VKILL:
		*dnep = (*chp = clp->orig.c_cc[VKILL]) == _POSIX_VDISABLE;
		break;
#ifdef VWERASE
	case KEY_VWERASE:
		*dnep = (*chp = clp->orig.c_cc[VWERASE]) == _POSIX_VDISABLE;
		break;
#endif
	default:
		*dnep = 1;
		break;
	}
	return (0);
}