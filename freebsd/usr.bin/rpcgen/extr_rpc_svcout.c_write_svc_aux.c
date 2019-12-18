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
 int /*<<< orphan*/  logflag ; 
 int /*<<< orphan*/  write_msg_out () ; 
 int /*<<< orphan*/  write_timeout_func () ; 

void
write_svc_aux(int nomain)
{
	if (!logflag)
		write_msg_out();
	if (!nomain)
		write_timeout_func();
}