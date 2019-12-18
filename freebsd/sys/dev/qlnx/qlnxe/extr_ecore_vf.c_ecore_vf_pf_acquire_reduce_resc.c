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
struct vf_pf_resc_request {int /*<<< orphan*/  num_cids; int /*<<< orphan*/  num_mc_filters; int /*<<< orphan*/  num_vlan_filters; int /*<<< orphan*/  num_mac_filters; int /*<<< orphan*/  num_sbs; int /*<<< orphan*/  num_rxqs; int /*<<< orphan*/  num_txqs; } ;
struct pf_vf_resc {int /*<<< orphan*/  num_cids; int /*<<< orphan*/  num_mc_filters; int /*<<< orphan*/  num_vlan_filters; int /*<<< orphan*/  num_mac_filters; int /*<<< orphan*/  num_sbs; int /*<<< orphan*/  num_rxqs; int /*<<< orphan*/  num_txqs; } ;
struct ecore_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECORE_MSG_IOV ; 

__attribute__((used)) static void ecore_vf_pf_acquire_reduce_resc(struct ecore_hwfn *p_hwfn,
					    struct vf_pf_resc_request *p_req,
					    struct pf_vf_resc *p_resp)
{
	DP_VERBOSE(p_hwfn, ECORE_MSG_IOV,
		   "PF unwilling to fullill resource request: rxq [%02x/%02x] txq [%02x/%02x] sbs [%02x/%02x] mac [%02x/%02x] vlan [%02x/%02x] mc [%02x/%02x] cids [%02x/%02x]. Try PF recommended amount\n",
		   p_req->num_rxqs, p_resp->num_rxqs,
		   p_req->num_rxqs, p_resp->num_txqs,
		   p_req->num_sbs, p_resp->num_sbs,
		   p_req->num_mac_filters, p_resp->num_mac_filters,
		   p_req->num_vlan_filters, p_resp->num_vlan_filters,
		   p_req->num_mc_filters, p_resp->num_mc_filters,
		   p_req->num_cids, p_resp->num_cids);

	/* humble our request */
	p_req->num_txqs = p_resp->num_txqs;
	p_req->num_rxqs = p_resp->num_rxqs;
	p_req->num_sbs = p_resp->num_sbs;
	p_req->num_mac_filters = p_resp->num_mac_filters;
	p_req->num_vlan_filters = p_resp->num_vlan_filters;
	p_req->num_mc_filters = p_resp->num_mc_filters;
	p_req->num_cids = p_resp->num_cids;
}