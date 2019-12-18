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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  OSAL_CPU_TO_LE16 (int) ; 

void ecore_rdma_set_fw_mac(u16 *p_fw_mac, u8 *p_ecore_mac)
{
	p_fw_mac[0] = OSAL_CPU_TO_LE16((p_ecore_mac[0] << 8) + p_ecore_mac[1]);
	p_fw_mac[1] = OSAL_CPU_TO_LE16((p_ecore_mac[2] << 8) + p_ecore_mac[3]);
	p_fw_mac[2] = OSAL_CPU_TO_LE16((p_ecore_mac[4] << 8) + p_ecore_mac[5]);
}