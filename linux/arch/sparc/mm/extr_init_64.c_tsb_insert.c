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
struct tsb {int dummy; } ;

/* Variables and functions */
 unsigned long __pa (unsigned long) ; 
 int /*<<< orphan*/  __tsb_insert (unsigned long,unsigned long,unsigned long) ; 
 scalar_t__ cheetah_plus ; 
 scalar_t__ hypervisor ; 
 scalar_t__ tlb_type ; 

__attribute__((used)) static inline void tsb_insert(struct tsb *ent, unsigned long tag, unsigned long pte)
{
	unsigned long tsb_addr = (unsigned long) ent;

	if (tlb_type == cheetah_plus || tlb_type == hypervisor)
		tsb_addr = __pa(tsb_addr);

	__tsb_insert(tsb_addr, tag, pte);
}