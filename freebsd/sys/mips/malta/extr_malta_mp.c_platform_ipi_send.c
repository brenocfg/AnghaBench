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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  C_SW1 ; 
 int /*<<< orphan*/  mftc0 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mttc0 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_thread_context (int) ; 

void
platform_ipi_send(int cpuid)
{
	uint32_t reg;

	set_thread_context(cpuid);

	/* Set cause */
	reg = mftc0(13, 0);
	reg |= (C_SW1);
	mttc0(13, 0, reg);
}