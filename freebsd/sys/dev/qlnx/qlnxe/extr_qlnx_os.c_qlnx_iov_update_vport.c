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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int __qlnx_iov_update_vport (void*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

int
qlnx_iov_update_vport(void *hwfn, uint8_t vfid, void *params, uint16_t *tlvs)
{
	return(__qlnx_iov_update_vport(hwfn, vfid, params, tlvs));
}