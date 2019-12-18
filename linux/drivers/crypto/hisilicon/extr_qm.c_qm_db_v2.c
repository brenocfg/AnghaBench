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
typedef  scalar_t__ u8 ;
typedef  int u64 ;
typedef  int u16 ;
struct hisi_qm {int io_base; } ;

/* Variables and functions */
 int QM_DB_CMD_SHIFT_V2 ; 
 int QM_DB_INDEX_SHIFT_V2 ; 
 int QM_DB_PRIORITY_SHIFT_V2 ; 
 int QM_DB_RAND_SHIFT_V2 ; 
 scalar_t__ QM_DOORBELL_CMD_CQ ; 
 scalar_t__ QM_DOORBELL_CMD_SQ ; 
 int QM_DOORBELL_EQ_AEQ_BASE_V2 ; 
 int QM_DOORBELL_SQ_CQ_BASE_V2 ; 
 int /*<<< orphan*/  writeq (int,int) ; 

__attribute__((used)) static void qm_db_v2(struct hisi_qm *qm, u16 qn, u8 cmd, u16 index, u8 priority)
{
	u64 doorbell;
	u64 dbase;
	u16 randata = 0;

	if (cmd == QM_DOORBELL_CMD_SQ || cmd == QM_DOORBELL_CMD_CQ)
		dbase = QM_DOORBELL_SQ_CQ_BASE_V2;
	else
		dbase = QM_DOORBELL_EQ_AEQ_BASE_V2;

	doorbell = qn | ((u64)cmd << QM_DB_CMD_SHIFT_V2) |
		   ((u64)randata << QM_DB_RAND_SHIFT_V2) |
		   ((u64)index << QM_DB_INDEX_SHIFT_V2)	 |
		   ((u64)priority << QM_DB_PRIORITY_SHIFT_V2);

	writeq(doorbell, qm->io_base + dbase);
}