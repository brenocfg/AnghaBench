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
struct opa_smp {scalar_t__ hop_ptr; scalar_t__ hop_cnt; } ;
struct ib_device {scalar_t__ process_mad; } ;
typedef  enum smi_action { ____Placeholder_smi_action } smi_action ;

/* Variables and functions */
 int IB_SMI_DISCARD ; 
 int IB_SMI_HANDLE ; 
 int /*<<< orphan*/  opa_get_smp_direction (struct opa_smp*) ; 

__attribute__((used)) static inline enum smi_action opa_smi_check_local_smp(struct opa_smp *smp,
						      struct ib_device *device)
{
	/* C14-9:3 -- We're at the end of the DR segment of path */
	/* C14-9:4 -- Hop Pointer = Hop Count + 1 -> give to SMA/SM */
	return (device->process_mad &&
		!opa_get_smp_direction(smp) &&
		(smp->hop_ptr == smp->hop_cnt + 1)) ?
		IB_SMI_HANDLE : IB_SMI_DISCARD;
}