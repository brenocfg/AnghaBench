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
struct vm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LAPIC_TRIG_LEVEL ; 
 int lapic_set_intr (struct vm*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline int
lapic_intr_level(struct vm *vm, int cpu, int vector)
{

	return (lapic_set_intr(vm, cpu, vector, LAPIC_TRIG_LEVEL));
}