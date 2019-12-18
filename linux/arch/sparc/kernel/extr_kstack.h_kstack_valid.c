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
struct thread_info {size_t cpu; } ;
struct sparc_stackf {int dummy; } ;

/* Variables and functions */
 unsigned long THREAD_SIZE ; 
 scalar_t__* hardirq_stack ; 
 scalar_t__* softirq_stack ; 

__attribute__((used)) static inline bool kstack_valid(struct thread_info *tp, unsigned long sp)
{
	unsigned long base = (unsigned long) tp;

	/* Stack pointer must be 16-byte aligned.  */
	if (sp & (16UL - 1))
		return false;

	if (sp >= (base + sizeof(struct thread_info)) &&
	    sp <= (base + THREAD_SIZE - sizeof(struct sparc_stackf)))
		return true;

	if (hardirq_stack[tp->cpu]) {
		base = (unsigned long) hardirq_stack[tp->cpu];
		if (sp >= base &&
		    sp <= (base + THREAD_SIZE - sizeof(struct sparc_stackf)))
			return true;
		base = (unsigned long) softirq_stack[tp->cpu];
		if (sp >= base &&
		    sp <= (base + THREAD_SIZE - sizeof(struct sparc_stackf)))
			return true;
	}
	return false;
}