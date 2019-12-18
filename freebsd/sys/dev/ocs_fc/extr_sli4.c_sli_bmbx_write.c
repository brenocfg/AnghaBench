#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_7__ {int /*<<< orphan*/  phys; } ;
struct TYPE_6__ {TYPE_5__ bmbx; int /*<<< orphan*/  os; } ;
typedef  TYPE_1__ sli4_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  SLI4_BMBX_DELAY_US ; 
 int /*<<< orphan*/  SLI4_BMBX_TIMEOUT_MSEC ; 
 int /*<<< orphan*/  SLI4_BMBX_WRITE_HI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLI4_BMBX_WRITE_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLI4_REG_BMBX ; 
 int /*<<< orphan*/  ocs_dma_sync (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_log_crit (int /*<<< orphan*/ ,char*) ; 
 int sli_bmbx_wait (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sli_reg_write (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t
sli_bmbx_write(sli4_t *sli4)
{
	uint32_t	val = 0;

	/* write buffer location to bootstrap mailbox register */
	ocs_dma_sync(&sli4->bmbx, OCS_DMASYNC_PREWRITE);
	val = SLI4_BMBX_WRITE_HI(sli4->bmbx.phys);
	sli_reg_write(sli4, SLI4_REG_BMBX, val);

	if (sli_bmbx_wait(sli4, SLI4_BMBX_DELAY_US)) {
		ocs_log_crit(sli4->os, "BMBX WRITE_HI failed\n");
		return -1;
	}
	val = SLI4_BMBX_WRITE_LO(sli4->bmbx.phys);
	sli_reg_write(sli4, SLI4_REG_BMBX, val);

	/* wait for SLI Port to set ready bit */
	return sli_bmbx_wait(sli4, SLI4_BMBX_TIMEOUT_MSEC/*XXX*/);
}