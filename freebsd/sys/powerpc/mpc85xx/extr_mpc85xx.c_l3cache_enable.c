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
 int /*<<< orphan*/  OCP85XX_CPC_CSR0 ; 
 int OCP85XX_CPC_CSR0_CE ; 
 int OCP85XX_CPC_CSR0_PE ; 
 int /*<<< orphan*/  ccsr_read4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccsr_write4 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
l3cache_enable(void)
{

	ccsr_write4(OCP85XX_CPC_CSR0, OCP85XX_CPC_CSR0_CE |
	    OCP85XX_CPC_CSR0_PE);
	/* Read back to sync write */
	ccsr_read4(OCP85XX_CPC_CSR0);
}