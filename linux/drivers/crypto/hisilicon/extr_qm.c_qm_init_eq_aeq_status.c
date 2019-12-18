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
struct hisi_qm_status {int eqc_phase; int aeqc_phase; scalar_t__ aeq_head; scalar_t__ eq_head; } ;
struct hisi_qm {struct hisi_qm_status status; } ;

/* Variables and functions */

__attribute__((used)) static void qm_init_eq_aeq_status(struct hisi_qm *qm)
{
	struct hisi_qm_status *status = &qm->status;

	status->eq_head = 0;
	status->aeq_head = 0;
	status->eqc_phase = 1;
	status->aeqc_phase = 1;
}