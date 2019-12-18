#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct ecore_ptt {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct ecore_hwfn {TYPE_1__ dmae_info; } ;
struct ecore_dmae_params {int dummy; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_DMAE_ADDRESS_GRC ; 
 int /*<<< orphan*/  ECORE_DMAE_ADDRESS_HOST_VIRT ; 
 int /*<<< orphan*/  OSAL_SPIN_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSAL_SPIN_UNLOCK (int /*<<< orphan*/ *) ; 
 int ecore_dmae_execute_command (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct ecore_dmae_params*) ; 

enum _ecore_status_t ecore_dmae_host2grc(struct ecore_hwfn *p_hwfn,
					 struct ecore_ptt *p_ptt,
					 u64 source_addr,
					 u32 grc_addr,
					 u32 size_in_dwords,
					 struct ecore_dmae_params *p_params)
{
	u32 grc_addr_in_dw = grc_addr / sizeof(u32);
	enum _ecore_status_t rc;

	OSAL_SPIN_LOCK(&p_hwfn->dmae_info.lock);

	rc = ecore_dmae_execute_command(p_hwfn, p_ptt, source_addr,
					grc_addr_in_dw,
					ECORE_DMAE_ADDRESS_HOST_VIRT,
					ECORE_DMAE_ADDRESS_GRC,
					size_in_dwords, p_params);

	OSAL_SPIN_UNLOCK(&p_hwfn->dmae_info.lock);

	return rc;
}