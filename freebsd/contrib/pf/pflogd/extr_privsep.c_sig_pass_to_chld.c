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
 int child_pid ; 
 int errno ; 
 int /*<<< orphan*/  kill (int,int) ; 

__attribute__((used)) static void
sig_pass_to_chld(int sig)
{
	int oerrno = errno;

	if (child_pid != -1)
		kill(child_pid, sig);
	errno = oerrno;
}