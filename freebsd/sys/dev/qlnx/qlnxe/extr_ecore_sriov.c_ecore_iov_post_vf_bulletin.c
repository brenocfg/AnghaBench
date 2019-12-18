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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int size; int /*<<< orphan*/  phys; struct ecore_bulletin_content* p_virt; } ;
struct ecore_vf_info {TYPE_1__ bulletin; int /*<<< orphan*/  vf_bulletin; int /*<<< orphan*/  abs_vf_id; int /*<<< orphan*/  relative_vf_id; } ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;
struct ecore_dmae_params {int /*<<< orphan*/  dst_vfid; int /*<<< orphan*/  flags; } ;
struct ecore_bulletin_content {int /*<<< orphan*/  crc; int /*<<< orphan*/  version; } ;
typedef  int /*<<< orphan*/  params ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECORE_DMAE_FLAG_VF_DST ; 
 int ECORE_INVAL ; 
 int /*<<< orphan*/  ECORE_MSG_IOV ; 
 int /*<<< orphan*/  OSAL_CRC32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  OSAL_MEMSET (struct ecore_dmae_params*,int /*<<< orphan*/ ,int) ; 
 int ecore_dmae_host2host (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct ecore_dmae_params*) ; 
 struct ecore_vf_info* ecore_iov_get_vf_info (struct ecore_hwfn*,int /*<<< orphan*/ ,int) ; 

enum _ecore_status_t ecore_iov_post_vf_bulletin(struct ecore_hwfn *p_hwfn,
						int vfid,
						struct ecore_ptt *p_ptt)
{
	struct ecore_bulletin_content *p_bulletin;
	int crc_size = sizeof(p_bulletin->crc);
	struct ecore_dmae_params params;
	struct ecore_vf_info *p_vf;

	p_vf = ecore_iov_get_vf_info(p_hwfn, (u16)vfid, true);
	if (!p_vf)
		return ECORE_INVAL;

	/* TODO - check VF is in a state where it can accept message */
	if (!p_vf->vf_bulletin)
		return ECORE_INVAL;

	p_bulletin = p_vf->bulletin.p_virt;

	/* Increment bulletin board version and compute crc */
	p_bulletin->version++;
	p_bulletin->crc = OSAL_CRC32(0, (u8 *)p_bulletin + crc_size,
				     p_vf->bulletin.size - crc_size);

	DP_VERBOSE(p_hwfn, ECORE_MSG_IOV,
		   "Posting Bulletin 0x%08x to VF[%d] (CRC 0x%08x)\n",
		   p_bulletin->version, p_vf->relative_vf_id,
		   p_bulletin->crc);

	/* propagate bulletin board via dmae to vm memory */
	OSAL_MEMSET(&params, 0, sizeof(params));
	params.flags = ECORE_DMAE_FLAG_VF_DST;
	params.dst_vfid = p_vf->abs_vf_id;
	return ecore_dmae_host2host(p_hwfn, p_ptt, p_vf->bulletin.phys,
				    p_vf->vf_bulletin, p_vf->bulletin.size / 4,
				    &params);
}