#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  value; } ;
struct TYPE_4__ {TYPE_1__ data; } ;
struct qlnxr_qp_hwq_info {TYPE_2__ db_data; scalar_t__ wqe_cons; scalar_t__ cons; scalar_t__ prod; int /*<<< orphan*/  pbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_chain_reset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
qlnxr_reset_qp_hwq_info(struct qlnxr_qp_hwq_info *qph)
{
	ecore_chain_reset(&qph->pbl);
	qph->prod = qph->cons = 0;
	qph->wqe_cons = 0;
	qph->db_data.data.value = cpu_to_le16(0);

	return;
}