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
typedef  scalar_t__ u32 ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;
struct ecore_dcbx_mib_meta_data {TYPE_1__* mib; int /*<<< orphan*/  size; int /*<<< orphan*/  addr; TYPE_1__* lldp_tlvs; TYPE_1__* lldp_remote; } ;
typedef  enum ecore_mib_read_type { ____Placeholder_ecore_mib_read_type } ecore_mib_read_type ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_2__ {scalar_t__ prefix_seq_num; scalar_t__ suffix_seq_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct ecore_hwfn*,char*,int,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int,int,scalar_t__,scalar_t__) ; 
 int ECORE_DCBX_LLDP_TLVS ; 
 int ECORE_DCBX_MAX_MIB_READ_TRY ; 
 int ECORE_DCBX_REMOTE_LLDP_MIB ; 
 int ECORE_IO ; 
 int /*<<< orphan*/  ECORE_MSG_DCB ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  ecore_memcpy_from (struct ecore_hwfn*,struct ecore_ptt*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum _ecore_status_t
ecore_dcbx_copy_mib(struct ecore_hwfn *p_hwfn,
		    struct ecore_ptt *p_ptt,
		    struct ecore_dcbx_mib_meta_data *p_data,
		    enum ecore_mib_read_type type)
{
	u32 prefix_seq_num, suffix_seq_num;
	int read_count = 0;
	enum _ecore_status_t rc = ECORE_SUCCESS;

	/* The data is considered to be valid only if both sequence numbers are
	 * the same.
	 */
	do {
		if (type == ECORE_DCBX_REMOTE_LLDP_MIB) {
			ecore_memcpy_from(p_hwfn, p_ptt, p_data->lldp_remote,
					  p_data->addr, p_data->size);
			prefix_seq_num = p_data->lldp_remote->prefix_seq_num;
			suffix_seq_num = p_data->lldp_remote->suffix_seq_num;
		} else if (type == ECORE_DCBX_LLDP_TLVS) {
			ecore_memcpy_from(p_hwfn, p_ptt, p_data->lldp_tlvs,
					  p_data->addr, p_data->size);
			prefix_seq_num = p_data->lldp_tlvs->prefix_seq_num;
			suffix_seq_num = p_data->lldp_tlvs->suffix_seq_num;

		} else {
			ecore_memcpy_from(p_hwfn, p_ptt, p_data->mib,
					  p_data->addr, p_data->size);
			prefix_seq_num = p_data->mib->prefix_seq_num;
			suffix_seq_num = p_data->mib->suffix_seq_num;
		}
		read_count++;

		DP_VERBOSE(p_hwfn, ECORE_MSG_DCB,
			   "mib type = %d, try count = %d prefix seq num  = %d suffix seq num = %d\n",
			   type, read_count, prefix_seq_num, suffix_seq_num);
	} while ((prefix_seq_num != suffix_seq_num) &&
		 (read_count < ECORE_DCBX_MAX_MIB_READ_TRY));

	if (read_count >= ECORE_DCBX_MAX_MIB_READ_TRY) {
		DP_ERR(p_hwfn,
		       "MIB read err, mib type = %d, try count = %d prefix seq num = %d suffix seq num = %d\n",
		       type, read_count, prefix_seq_num, suffix_seq_num);
		rc = ECORE_IO;
	}

	return rc;
}