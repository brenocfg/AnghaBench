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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_3__ {int num_popped; int /*<<< orphan*/  qid; scalar_t__ event; int /*<<< orphan*/  rearm; } ;
struct TYPE_4__ {int /*<<< orphan*/  dw0; TYPE_1__ bits; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ cq_db_t ;
typedef  int /*<<< orphan*/  POCE_SOFTC ;

/* Variables and functions */
 int /*<<< orphan*/  OCE_WRITE_REG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PD_CQ_DB ; 
 int /*<<< orphan*/  db ; 

void oce_arm_cq(POCE_SOFTC sc, int16_t qid, int npopped, uint32_t rearm)
{
	cq_db_t cq_db = { 0 };

	cq_db.bits.rearm = rearm;
	cq_db.bits.num_popped = npopped;
	cq_db.bits.event = 0;
	cq_db.bits.qid = qid;
	OCE_WRITE_REG32(sc, db, PD_CQ_DB, cq_db.dw0);

}