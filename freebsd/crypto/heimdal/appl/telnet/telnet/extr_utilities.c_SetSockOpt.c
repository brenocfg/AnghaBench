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

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int setsockopt (int,int,int,void*,int) ; 
 int /*<<< orphan*/  stderr ; 

int
SetSockOpt(int fd, int level, int option, int yesno)
{
#ifdef HAVE_SETSOCKOPT
#ifndef	NOT43
    return setsockopt(fd, level, option,
				(void *)&yesno, sizeof yesno);
#else	/* NOT43 */
    if (yesno == 0) {		/* Can't do that in 4.2! */
	fprintf(stderr, "Error: attempt to turn off an option 0x%x.\n",
				option);
	return -1;
    }
    return setsockopt(fd, level, option, 0, 0);
#endif	/* NOT43 */
#else
    return -1;
#endif
}