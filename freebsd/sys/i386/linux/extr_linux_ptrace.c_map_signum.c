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
 int SIGSTOP ; 
 int linux_to_bsd_signal (int) ; 

__attribute__((used)) static __inline int
map_signum(int signum)
{

	signum = linux_to_bsd_signal(signum);
	return ((signum == SIGSTOP)? 0 : signum);
}