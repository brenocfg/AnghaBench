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
 int /*<<< orphan*/  ERR_JOBCONTROL ; 
 int /*<<< orphan*/  ERR_JOBCTRLSUB ; 
 int /*<<< orphan*/  stderror (int /*<<< orphan*/ ) ; 
 int tpgrp ; 

__attribute__((used)) static void
okpcntl(void)
{
    if (tpgrp == -1)
	stderror(ERR_JOBCONTROL);
    if (tpgrp == 0)
	stderror(ERR_JOBCTRLSUB);
}