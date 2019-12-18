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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  __qlnx_osal_iov_vf_cleanup (void*,int /*<<< orphan*/ ) ; 

void
qlnx_osal_iov_vf_cleanup(void *p_hwfn, uint8_t relative_vf_id)
{
	__qlnx_osal_iov_vf_cleanup(p_hwfn, relative_vf_id);
	return;
}