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
 int /*<<< orphan*/  SYS1_HRSTOUTC ; 
 int /*<<< orphan*/  SYSCTL_SYS1 ; 
 int /*<<< orphan*/  sysctl_w32 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void falcon_trigger_hrst(int level)
{
	sysctl_w32(SYSCTL_SYS1, level & 1, SYS1_HRSTOUTC);
}