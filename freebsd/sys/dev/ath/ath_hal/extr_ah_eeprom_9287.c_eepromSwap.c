#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  void* uint16_t ;
struct TYPE_10__ {size_t antCtrlCommon; size_t* antCtrlChain; TYPE_3__* spurChans; } ;
struct TYPE_7__ {void* deviceCap; void* blueToothOptions; void* rfSilent; void** regDmn; void* version; void* checksum; void* length; } ;
struct TYPE_8__ {TYPE_4__ modalHeader; TYPE_1__ baseEepHeader; } ;
struct TYPE_11__ {TYPE_2__ ee_base; } ;
struct TYPE_9__ {void* spurChan; } ;
typedef  TYPE_4__ MODAL_EEP_9287_HEADER ;
typedef  TYPE_5__ HAL_EEPROM_9287 ;

/* Variables and functions */
 size_t AR5416_EEPROM_MODAL_SPURS ; 
 size_t AR9287_MAX_CHAINS ; 
 void* __bswap16 (void*) ; 
 size_t __bswap32 (size_t) ; 

__attribute__((used)) static void
eepromSwap(HAL_EEPROM_9287 *ee)
{
	uint32_t integer, i;
	uint16_t word;
	MODAL_EEP_9287_HEADER *pModal;

	/* convert Base Eep header */
	word = __bswap16(ee->ee_base.baseEepHeader.length);
	ee->ee_base.baseEepHeader.length = word;

	word = __bswap16(ee->ee_base.baseEepHeader.checksum);
	ee->ee_base.baseEepHeader.checksum = word;

	word = __bswap16(ee->ee_base.baseEepHeader.version);
	ee->ee_base.baseEepHeader.version = word;

	word = __bswap16(ee->ee_base.baseEepHeader.regDmn[0]);
	ee->ee_base.baseEepHeader.regDmn[0] = word;

	word = __bswap16(ee->ee_base.baseEepHeader.regDmn[1]);
	ee->ee_base.baseEepHeader.regDmn[1] = word;

	word = __bswap16(ee->ee_base.baseEepHeader.rfSilent);
	ee->ee_base.baseEepHeader.rfSilent = word;

	word = __bswap16(ee->ee_base.baseEepHeader.blueToothOptions);
	ee->ee_base.baseEepHeader.blueToothOptions = word; 

	word = __bswap16(ee->ee_base.baseEepHeader.deviceCap);
	ee->ee_base.baseEepHeader.deviceCap = word;

	/* convert Modal Eep header */

	/* only 2.4ghz here; so only one modal header entry */
	pModal = &ee->ee_base.modalHeader;

	/* XXX linux/ah_osdep.h only defines __bswap32 for BE */
	integer = __bswap32(pModal->antCtrlCommon);
	pModal->antCtrlCommon = integer;

	for (i = 0; i < AR9287_MAX_CHAINS; i++) {
		integer = __bswap32(pModal->antCtrlChain[i]);
		pModal->antCtrlChain[i] = integer;
	}
	for (i = 0; i < AR5416_EEPROM_MODAL_SPURS; i++) {
		word = __bswap16(pModal->spurChans[i].spurChan);
		pModal->spurChans[i].spurChan = word;
	}
}