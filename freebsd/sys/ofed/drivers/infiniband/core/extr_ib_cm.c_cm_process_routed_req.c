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
struct ib_wc {int /*<<< orphan*/  dlid_path_bits; int /*<<< orphan*/  sl; int /*<<< orphan*/  slid; } ;
struct cm_req_msg {scalar_t__ primary_local_lid; scalar_t__ primary_remote_lid; scalar_t__ alt_local_lid; scalar_t__ alt_remote_lid; } ;

/* Variables and functions */
 scalar_t__ IB_LID_PERMISSIVE ; 
 int /*<<< orphan*/  cm_req_get_alt_subnet_local (struct cm_req_msg*) ; 
 int /*<<< orphan*/  cm_req_get_primary_subnet_local (struct cm_req_msg*) ; 
 int /*<<< orphan*/  cm_req_set_alt_sl (struct cm_req_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cm_req_set_primary_sl (struct cm_req_msg*,int /*<<< orphan*/ ) ; 
 void* cpu_to_be16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cm_process_routed_req(struct cm_req_msg *req_msg, struct ib_wc *wc)
{
	if (!cm_req_get_primary_subnet_local(req_msg)) {
		if (req_msg->primary_local_lid == IB_LID_PERMISSIVE) {
			req_msg->primary_local_lid = cpu_to_be16(wc->slid);
			cm_req_set_primary_sl(req_msg, wc->sl);
		}

		if (req_msg->primary_remote_lid == IB_LID_PERMISSIVE)
			req_msg->primary_remote_lid = cpu_to_be16(wc->dlid_path_bits);
	}

	if (!cm_req_get_alt_subnet_local(req_msg)) {
		if (req_msg->alt_local_lid == IB_LID_PERMISSIVE) {
			req_msg->alt_local_lid = cpu_to_be16(wc->slid);
			cm_req_set_alt_sl(req_msg, wc->sl);
		}

		if (req_msg->alt_remote_lid == IB_LID_PERMISSIVE)
			req_msg->alt_remote_lid = cpu_to_be16(wc->dlid_path_bits);
	}
}