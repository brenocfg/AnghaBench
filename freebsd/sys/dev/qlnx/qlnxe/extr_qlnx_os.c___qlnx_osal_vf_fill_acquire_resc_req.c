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
struct ecore_vf_acquire_sw_info {int driver_version; int /*<<< orphan*/  os_type; } ;
struct ecore_hwfn {int dummy; } ;

/* Variables and functions */
 int QLNX_VERSION_BUILD ; 
 int QLNX_VERSION_MAJOR ; 
 int QLNX_VERSION_MINOR ; 
 int /*<<< orphan*/  VFPF_ACQUIRE_OS_FREEBSD ; 

__attribute__((used)) static void
__qlnx_osal_vf_fill_acquire_resc_req(struct ecore_hwfn *p_hwfn,
	struct ecore_vf_acquire_sw_info *p_sw_info)
{
	p_sw_info->driver_version = (QLNX_VERSION_MAJOR << 24) |
					(QLNX_VERSION_MINOR << 16) |
					 QLNX_VERSION_BUILD;
	p_sw_info->os_type = VFPF_ACQUIRE_OS_FREEBSD;

	return;
}