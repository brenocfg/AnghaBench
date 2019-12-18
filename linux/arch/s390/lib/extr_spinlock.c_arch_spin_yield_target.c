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
struct spin_wait {int node_id; struct spin_wait* prev; } ;

/* Variables and functions */
 int _Q_LOCK_CPU_MASK ; 
 int _Q_TAIL_CPU_OFFSET ; 

__attribute__((used)) static inline int arch_spin_yield_target(int lock, struct spin_wait *node)
{
	if (lock & _Q_LOCK_CPU_MASK)
		return lock & _Q_LOCK_CPU_MASK;
	if (node == NULL || node->prev == NULL)
		return 0;	/* 0 -> no target cpu */
	while (node->prev)
		node = node->prev;
	return node->node_id >> _Q_TAIL_CPU_OFFSET;
}