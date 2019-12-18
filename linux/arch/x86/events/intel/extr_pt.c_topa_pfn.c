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
struct topa {int dummy; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  PFN_DOWN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  topa_to_page (struct topa*) ; 
 int /*<<< orphan*/  virt_to_phys (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline phys_addr_t topa_pfn(struct topa *topa)
{
	return PFN_DOWN(virt_to_phys(topa_to_page(topa)));
}