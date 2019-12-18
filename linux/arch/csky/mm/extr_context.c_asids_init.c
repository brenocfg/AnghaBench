#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * reserved; int /*<<< orphan*/ * active; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int CONFIG_CPU_ASID_BITS ; 
 int /*<<< orphan*/  NUM_ASIDS (TYPE_1__*) ; 
 int /*<<< orphan*/  NUM_CTXT_ASIDS (TYPE_1__*) ; 
 int /*<<< orphan*/  active_asids ; 
 scalar_t__ asid_allocator_init (TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asid_flush_cpu_ctxt ; 
 TYPE_1__ asid_info ; 
 int num_possible_cpus () ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reserved_asids ; 

__attribute__((used)) static int asids_init(void)
{
	BUG_ON(((1 << CONFIG_CPU_ASID_BITS) - 1) <= num_possible_cpus());

	if (asid_allocator_init(&asid_info, CONFIG_CPU_ASID_BITS, 1,
				asid_flush_cpu_ctxt))
		panic("Unable to initialize ASID allocator for %lu ASIDs\n",
		      NUM_ASIDS(&asid_info));

	asid_info.active = &active_asids;
	asid_info.reserved = &reserved_asids;

	pr_info("ASID allocator initialised with %lu entries\n",
		NUM_CTXT_ASIDS(&asid_info));

	return 0;
}