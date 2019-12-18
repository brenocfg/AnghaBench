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
typedef  scalar_t__ u8 ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {struct ecore_dev* p_dev; } ;
struct ecore_dev {TYPE_1__* p_llh_info; } ;
typedef  enum ecore_eng { ____Placeholder_ecore_eng } ecore_eng ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_2__ {scalar_t__ num_ppfid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_dev*,int,char*,...) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_dev*,int /*<<< orphan*/ ,char*,int) ; 
 int ECORE_BOTH_ENG ; 
 int ECORE_ENG0 ; 
 scalar_t__ ECORE_IS_FCOE_PERSONALITY (struct ecore_hwfn*) ; 
 scalar_t__ ECORE_IS_ISCSI_PERSONALITY (struct ecore_hwfn*) ; 
 scalar_t__ ECORE_IS_ROCE_PERSONALITY (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ECORE_MSG_SP ; 
 int ECORE_SUCCESS ; 
 int __ecore_llh_set_engine_affin (struct ecore_hwfn*,struct ecore_ptt*) ; 
 int ecore_llh_set_ppfid_affinity (struct ecore_dev*,scalar_t__,int) ; 
 int ecore_llh_set_roce_affinity (struct ecore_dev*,int) ; 

__attribute__((used)) static enum _ecore_status_t
ecore_llh_set_engine_affin(struct ecore_hwfn *p_hwfn, struct ecore_ptt *p_ptt,
			   bool avoid_eng_affin)
{
	struct ecore_dev *p_dev = p_hwfn->p_dev;
	enum _ecore_status_t rc;

	/* Backwards compatible mode:
	 * - RoCE packets     - Use engine 0.
	 * - Non-RoCE packets - Use connection based classification for L2 PFs,
	 *                      and engine 0 otherwise.
	 */
	if (avoid_eng_affin) {
		enum ecore_eng eng;
		u8 ppfid;

		if (ECORE_IS_ROCE_PERSONALITY(p_hwfn)) {
			eng = ECORE_ENG0;
			rc = ecore_llh_set_roce_affinity(p_dev, eng);
			if (rc != ECORE_SUCCESS) {
				DP_NOTICE(p_dev, false,
					  "Failed to set the RoCE engine affinity\n");
				return rc;
			}

			DP_VERBOSE(p_dev, ECORE_MSG_SP,
				   "LLH [backwards compatible mode]: Set the engine affinity of RoCE packets as %d\n",
				   eng);
		}

		eng = (ECORE_IS_FCOE_PERSONALITY(p_hwfn) ||
		       ECORE_IS_ISCSI_PERSONALITY(p_hwfn)) ? ECORE_ENG0
							   : ECORE_BOTH_ENG;
		for (ppfid = 0; ppfid < p_dev->p_llh_info->num_ppfid; ppfid++) {
			rc = ecore_llh_set_ppfid_affinity(p_dev, ppfid, eng);
			if (rc != ECORE_SUCCESS) {
				DP_NOTICE(p_dev, false,
					  "Failed to set the engine affinity of ppfid %d\n",
					  ppfid);
				return rc;
			}
		}

		DP_VERBOSE(p_dev, ECORE_MSG_SP,
			   "LLH [backwards compatible mode]: Set the engine affinity of non-RoCE packets as %d\n",
			   eng);

		return ECORE_SUCCESS;
	}

	return __ecore_llh_set_engine_affin(p_hwfn, p_ptt);
}