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
struct hisi_zip {int /*<<< orphan*/  qm; } ;

/* Variables and functions */
 int QM_ACC_WB_NOT_READY_TIMEOUT ; 
 int /*<<< orphan*/  QM_BASE_CE ; 
 int QM_BASE_NFE ; 
 int /*<<< orphan*/  QM_DB_RANDOM_INVALID ; 
 int /*<<< orphan*/  hisi_qm_hw_error_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_zip_hw_error_set_state (struct hisi_zip*,int) ; 

__attribute__((used)) static void hisi_zip_hw_error_init(struct hisi_zip *hisi_zip)
{
	hisi_qm_hw_error_init(&hisi_zip->qm, QM_BASE_CE,
			      QM_BASE_NFE | QM_ACC_WB_NOT_READY_TIMEOUT, 0,
			      QM_DB_RANDOM_INVALID);
	hisi_zip_hw_error_set_state(hisi_zip, true);
}