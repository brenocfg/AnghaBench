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
 int /*<<< orphan*/  ASI_LSU_CTL_REG ; 
 int LSU_PW ; 
 int ldxa (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stxa_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
watch_phys_clear()
{
	stxa_sync(0, ASI_LSU_CTL_REG,
	    ldxa(0, ASI_LSU_CTL_REG) & ~LSU_PW);
}