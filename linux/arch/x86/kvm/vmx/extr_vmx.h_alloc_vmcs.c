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
struct vmcs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL_ACCOUNT ; 
 struct vmcs* alloc_vmcs_cpu (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_smp_processor_id () ; 

__attribute__((used)) static inline struct vmcs *alloc_vmcs(bool shadow)
{
	return alloc_vmcs_cpu(shadow, raw_smp_processor_id(),
			      GFP_KERNEL_ACCOUNT);
}