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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_pkru_value ; 
 int /*<<< orphan*/  write_pkru (int /*<<< orphan*/ ) ; 

void copy_init_pkru_to_fpregs(void)
{
	u32 init_pkru_value_snapshot = READ_ONCE(init_pkru_value);
	/*
	 * Override the PKRU state that came from 'init_fpstate'
	 * with the baseline from the process.
	 */
	write_pkru(init_pkru_value_snapshot);
}