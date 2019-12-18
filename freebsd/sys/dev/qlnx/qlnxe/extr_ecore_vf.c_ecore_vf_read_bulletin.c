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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ size; struct ecore_bulletin_content* p_virt; } ;
struct ecore_bulletin_content {scalar_t__ version; int crc; } ;
struct ecore_vf_iov {TYPE_1__ bulletin; struct ecore_bulletin_content bulletin_shadow; } ;
struct ecore_hwfn {struct ecore_vf_iov* vf_iov_info; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int ECORE_AGAIN ; 
 int /*<<< orphan*/  ECORE_MSG_IOV ; 
 int ECORE_SUCCESS ; 
 int OSAL_CRC32 (int /*<<< orphan*/ ,int*,scalar_t__) ; 
 int /*<<< orphan*/  OSAL_MEMCPY (struct ecore_bulletin_content*,struct ecore_bulletin_content*,scalar_t__) ; 

enum _ecore_status_t ecore_vf_read_bulletin(struct ecore_hwfn *p_hwfn,
					    u8 *p_change)
{
	struct ecore_vf_iov *p_iov = p_hwfn->vf_iov_info;
	struct ecore_bulletin_content shadow;
	u32 crc, crc_size;

	crc_size = sizeof(p_iov->bulletin.p_virt->crc);
	*p_change = 0;

	/* Need to guarantee PF is not in the middle of writing it */
	OSAL_MEMCPY(&shadow, p_iov->bulletin.p_virt, p_iov->bulletin.size);

	/* If version did not update, no need to do anything */
	if (shadow.version == p_iov->bulletin_shadow.version)
		return ECORE_SUCCESS;

	/* Verify the bulletin we see is valid */
	crc = OSAL_CRC32(0, (u8 *)&shadow + crc_size,
			 p_iov->bulletin.size - crc_size);
	if (crc != shadow.crc)
		return ECORE_AGAIN;

	/* Set the shadow bulletin and process it */
	OSAL_MEMCPY(&p_iov->bulletin_shadow, &shadow, p_iov->bulletin.size);

	DP_VERBOSE(p_hwfn, ECORE_MSG_IOV,
		   "Read a bulletin update %08x\n", shadow.version);

	*p_change = 1;

	return ECORE_SUCCESS;
}