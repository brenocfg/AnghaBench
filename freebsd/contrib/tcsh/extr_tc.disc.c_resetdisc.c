#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ioctl_t ;

/* Variables and functions */
 int /*<<< orphan*/  TCSETAF ; 
 int /*<<< orphan*/  TIOCSETD ; 
 int /*<<< orphan*/  TXDELCD ; 
 int /*<<< orphan*/  USE (int) ; 
 scalar_t__ add_discipline ; 
 int ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oldisc ; 
 int /*<<< orphan*/  otermiob ; 
 scalar_t__ strPOSIX ; 

int
/*ARGSUSED*/
resetdisc(int f)
{
    if (add_discipline) {
	add_discipline = 0;
#if defined(OREO) || defined(IRIS4D)
	return (ioctl(f, TCSETAF, (ioctl_t) & otermiob));
#endif /* OREO || IRIS4D */

#ifdef _IBMR2
	return (ioctl(f, TXDELCD, (ioctl_t) strPOSIX));
#endif /* _IBMR2 */

#ifndef HAVE_DISC
# if defined(TIOCSETD) && defined(NTTYDISC)
	return (ioctl(f, TIOCSETD, (ioctl_t) & oldisc));
# endif /* TIOCSETD && NTTYDISC */
#endif /* !HAVE_DISC */
    }
    USE(f);
    return (0);
}