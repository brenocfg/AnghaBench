#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* status ) (int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mce_num_banks ; 
 int /*<<< orphan*/  mce_wrmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ msr_ops ; 
 int /*<<< orphan*/  stub1 (int) ; 
 scalar_t__ test_bit (int,unsigned long*) ; 
 int this_cpu_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mce_clear_state(unsigned long *toclear)
{
	int i;

	for (i = 0; i < this_cpu_read(mce_num_banks); i++) {
		if (test_bit(i, toclear))
			mce_wrmsrl(msr_ops.status(i), 0);
	}
}