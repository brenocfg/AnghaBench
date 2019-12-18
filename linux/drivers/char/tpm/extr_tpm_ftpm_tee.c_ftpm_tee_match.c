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
struct tee_ioctl_version_data {scalar_t__ impl_id; int gen_caps; } ;

/* Variables and functions */
 int TEE_GEN_CAP_GP ; 
 scalar_t__ TEE_IMPL_ID_OPTEE ; 

__attribute__((used)) static int ftpm_tee_match(struct tee_ioctl_version_data *ver, const void *data)
{
	/*
	 * Currently this driver only support GP Complaint OPTEE based fTPM TA
	 */
	if ((ver->impl_id == TEE_IMPL_ID_OPTEE) &&
		(ver->gen_caps & TEE_GEN_CAP_GP))
		return 1;
	else
		return 0;
}