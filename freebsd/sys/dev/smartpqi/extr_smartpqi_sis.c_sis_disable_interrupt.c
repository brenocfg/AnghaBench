#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int intr_type; } ;
typedef  TYPE_1__ pqisrc_softstate_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_ERR (char*) ; 
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
#define  INTR_TYPE_FIXED 130 
#define  INTR_TYPE_MSI 129 
#define  INTR_TYPE_MSIX 128 
 int /*<<< orphan*/  pqisrc_configure_legacy_intx (TYPE_1__*,int) ; 
 int /*<<< orphan*/  sis_disable_intx (TYPE_1__*) ; 
 int /*<<< orphan*/  sis_disable_msix (TYPE_1__*) ; 

void sis_disable_interrupt(pqisrc_softstate_t *softs)
{
	DBG_FUNC("IN");
	
	switch(softs->intr_type) {
		case INTR_TYPE_FIXED:
			pqisrc_configure_legacy_intx(softs,false);
			sis_disable_intx(softs);
			break;
		case INTR_TYPE_MSI:
		case INTR_TYPE_MSIX:
			sis_disable_msix(softs);
			break;
		default:
			DBG_ERR("Inerrupt mode none!\n");
			break;
	}
	
	DBG_FUNC("OUT");
}