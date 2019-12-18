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
struct octeon_device {int /*<<< orphan*/ * instr_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  lio_flush_iq (struct octeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_mdelay (int) ; 
 int /*<<< orphan*/  lio_process_ordered_list (struct octeon_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
lio_sleep_cond(struct octeon_device *oct, volatile int *condition)
{

	while (!(*condition)) {
		lio_mdelay(1);
		lio_flush_iq(oct, oct->instr_queue[0], 0);
		lio_process_ordered_list(oct, 0);
	}
}