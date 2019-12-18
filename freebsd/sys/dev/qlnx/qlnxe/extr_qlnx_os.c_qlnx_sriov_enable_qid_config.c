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
typedef  size_t u16 ;
struct ecore_iov_vf_init_params {size_t num_queues; size_t rel_vf_id; size_t* req_rx_queue; size_t* req_tx_queue; size_t vport_id; size_t rss_eng_id; } ;
struct ecore_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_PF_L2_QUE ; 
 size_t FEAT_NUM (struct ecore_hwfn*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
qlnx_sriov_enable_qid_config(struct ecore_hwfn *hwfn, u16 vfid,
	struct ecore_iov_vf_init_params *params)
{
        u16 base, i;

        /* Since we have an equal resource distribution per-VF, and we assume
         * PF has acquired the ECORE_PF_L2_QUE first queues, we start setting
         * sequentially from there.
         */
        base = FEAT_NUM(hwfn, ECORE_PF_L2_QUE) + vfid * params->num_queues;

        params->rel_vf_id = vfid;

        for (i = 0; i < params->num_queues; i++) {
                params->req_rx_queue[i] = base + i;
                params->req_tx_queue[i] = base + i;
        }

        /* PF uses indices 0 for itself; Set vport/RSS afterwards */
        params->vport_id = vfid + 1;
        params->rss_eng_id = vfid + 1;

	return;
}