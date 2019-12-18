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
typedef  int u_long ;
struct TYPE_3__ {int /*<<< orphan*/  orig; } ;
typedef  int /*<<< orphan*/  SCR ;
typedef  TYPE_1__ CL_PRIVATE ;

/* Variables and functions */
#define  B110 136 
#define  B1200 135 
#define  B134 134 
#define  B150 133 
#define  B200 132 
#define  B300 131 
#define  B50 130 
#define  B600 129 
#define  B75 128 
 TYPE_1__* CLP (int /*<<< orphan*/ *) ; 
 int cfgetospeed (int /*<<< orphan*/ *) ; 

int
cl_baud(SCR *sp, u_long *ratep)
{
	CL_PRIVATE *clp;

	/*
	 * XXX
	 * There's no portable way to get a "baud rate" -- cfgetospeed(3)
	 * returns the value associated with some #define, which we may
	 * never have heard of, or which may be a purely local speed.  Vi
	 * only cares if it's SLOW (w300), slow (w1200) or fast (w9600).
	 * Try and detect the slow ones, and default to fast.
	 */
	clp = CLP(sp);
	switch (cfgetospeed(&clp->orig)) {
	case B50:
	case B75:
	case B110:
	case B134:
	case B150:
	case B200:
	case B300:
	case B600:
		*ratep = 600;
		break;
	case B1200:
		*ratep = 1200;
		break;
	default:
		*ratep = 9600;
		break;
	}
	return (0);
}