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
struct nitrox_cmdq {int /*<<< orphan*/  pending_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 

__attribute__((used)) static inline bool cmdq_full(struct nitrox_cmdq *cmdq, int qlen)
{
	if (atomic_inc_return(&cmdq->pending_count) > qlen) {
		atomic_dec(&cmdq->pending_count);
		/* sync with other cpus */
		smp_mb__after_atomic();
		return true;
	}
	/* sync with other cpus */
	smp_mb__after_atomic();
	return false;
}