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
 int /*<<< orphan*/  TELQUAL_INFO ; 
 int /*<<< orphan*/  env_opt_start () ; 
 int /*<<< orphan*/ * opt_replyp ; 

void
env_opt_start_info(void)
{
	env_opt_start();
	if (opt_replyp)
	    opt_replyp[-1] = TELQUAL_INFO;
}