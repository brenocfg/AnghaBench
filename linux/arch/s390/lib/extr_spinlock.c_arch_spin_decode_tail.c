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
struct spin_wait {int dummy; } ;

/* Variables and functions */
 int _Q_TAIL_CPU_MASK ; 
 int _Q_TAIL_CPU_OFFSET ; 
 int _Q_TAIL_IDX_MASK ; 
 int _Q_TAIL_IDX_OFFSET ; 
 struct spin_wait* per_cpu_ptr (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * spin_wait ; 

__attribute__((used)) static inline struct spin_wait *arch_spin_decode_tail(int lock)
{
	int ix, cpu;

	ix = (lock & _Q_TAIL_IDX_MASK) >> _Q_TAIL_IDX_OFFSET;
	cpu = (lock & _Q_TAIL_CPU_MASK) >> _Q_TAIL_CPU_OFFSET;
	return per_cpu_ptr(&spin_wait[ix], cpu - 1);
}