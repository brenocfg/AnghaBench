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
 int PSR_F ; 
 int PSR_I ; 
 int /*<<< orphan*/  cninit_finish () ; 
 scalar_t__ cold ; 
 int /*<<< orphan*/  enable_interrupts (int) ; 

__attribute__((used)) static void
configure_final(void *dummy)
{

	enable_interrupts(PSR_I | PSR_F);
	cninit_finish();
	cold = 0;
}