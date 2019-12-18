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
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  dpm_complete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpm_resume (int /*<<< orphan*/ ) ; 

void dpm_resume_end(pm_message_t state)
{
	dpm_resume(state);
	dpm_complete(state);
}