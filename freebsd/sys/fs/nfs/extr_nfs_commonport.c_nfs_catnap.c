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
 int EINTR ; 
 int NFSERR_GRACE ; 
 int hz ; 
 int tsleep (int*,int,char const*,int) ; 

int
nfs_catnap(int prio, int errval, const char *wmesg)
{
	static int non_event;
	int ret;

	if (errval == NFSERR_GRACE)
		ret = tsleep(&non_event, prio, wmesg, 5 * hz);
	else
		ret = tsleep(&non_event, prio, wmesg, 1);
	if (ret != EINTR)
		ret = 0;
	return (ret);
}