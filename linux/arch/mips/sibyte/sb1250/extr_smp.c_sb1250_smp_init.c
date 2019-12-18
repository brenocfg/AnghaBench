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
 int /*<<< orphan*/  ST0_IM ; 
 unsigned int STATUSF_IP0 ; 
 unsigned int STATUSF_IP1 ; 
 unsigned int STATUSF_IP2 ; 
 unsigned int STATUSF_IP3 ; 
 unsigned int STATUSF_IP4 ; 
 int /*<<< orphan*/  change_c0_status (int /*<<< orphan*/ ,unsigned int) ; 

void sb1250_smp_init(void)
{
	unsigned int imask = STATUSF_IP4 | STATUSF_IP3 | STATUSF_IP2 |
		STATUSF_IP1 | STATUSF_IP0;

	/* Set interrupt mask, but don't enable */
	change_c0_status(ST0_IM, imask);
}