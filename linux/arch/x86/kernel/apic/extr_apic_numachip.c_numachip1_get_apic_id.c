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

/* Variables and functions */
 int /*<<< orphan*/  MSR_FAM10H_NODE_ID ; 
 int /*<<< orphan*/  X86_FEATURE_NODEID_MSR ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ static_cpu_has (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int numachip1_get_apic_id(unsigned long x)
{
	unsigned long value;
	unsigned int id = (x >> 24) & 0xff;

	if (static_cpu_has(X86_FEATURE_NODEID_MSR)) {
		rdmsrl(MSR_FAM10H_NODE_ID, value);
		id |= (value << 2) & 0xff00;
	}

	return id;
}