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
typedef  size_t uint32_t ;
struct octeon_device {TYPE_1__** instr_queue; } ;
struct TYPE_2__ {int max_count; int /*<<< orphan*/  instr_pending; } ;

/* Variables and functions */
 int atomic_load_acq_int (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int
lio_iq_is_full(struct octeon_device *oct, uint32_t q_no)
{

	return (atomic_load_acq_int(&oct->instr_queue[q_no]->instr_pending) >=
		(oct->instr_queue[q_no]->max_count - 2));
}