#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_8__ {TYPE_1__* ioa_reg; } ;
typedef  TYPE_2__ pqisrc_softstate_t ;
struct TYPE_7__ {int /*<<< orphan*/  host_to_ioa_db; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_ERR (char*) ; 
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int /*<<< orphan*/  LEGACY_SIS_IDBR ; 
 int /*<<< orphan*/  PCI_MEM_GET32 (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_MEM_PUT32 (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PQI_STATUS_SUCCESS ; 
 int /*<<< orphan*/  SIS_ENABLE_INTX ; 
 scalar_t__ pqisrc_sis_wait_for_db_bit_to_clear (TYPE_2__*,int /*<<< orphan*/ ) ; 

void sis_enable_intx(pqisrc_softstate_t *softs)
{
	uint32_t db_reg;

	DBG_FUNC("IN\n");

	db_reg = PCI_MEM_GET32(softs, &softs->ioa_reg->host_to_ioa_db,
			LEGACY_SIS_IDBR);
	db_reg |= SIS_ENABLE_INTX;
	PCI_MEM_PUT32(softs, &softs->ioa_reg->host_to_ioa_db,
			LEGACY_SIS_IDBR, db_reg);
	if (pqisrc_sis_wait_for_db_bit_to_clear(softs,SIS_ENABLE_INTX) 
			!= PQI_STATUS_SUCCESS) {
		DBG_ERR("Failed to wait for enable intx db bit to clear\n");
	}
	DBG_FUNC("OUT\n");
}