#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_3__ {scalar_t__ phys_id; } ;
struct bnxt_cp_ring {scalar_t__ cons; TYPE_1__ ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_CP_ENABLE_DB (TYPE_1__*) ; 
 int /*<<< orphan*/  BNXT_CP_IDX_ENABLE_DB (TYPE_1__*,scalar_t__) ; 
 scalar_t__ HWRM_NA_SIGNATURE ; 
 scalar_t__ UINT32_MAX ; 

__attribute__((used)) static void inline
bnxt_do_enable_intr(struct bnxt_cp_ring *cpr)
{
	if (cpr->ring.phys_id != (uint16_t)HWRM_NA_SIGNATURE) {
		/* First time enabling, do not set index */
		if (cpr->cons == UINT32_MAX)
			BNXT_CP_ENABLE_DB(&cpr->ring);
		else
			BNXT_CP_IDX_ENABLE_DB(&cpr->ring, cpr->cons);
	}
}