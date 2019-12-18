#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  void* uint16_t ;
struct TYPE_6__ {size_t antCtrlCommon; size_t* antCtrlChain; TYPE_2__* spurChans; } ;
struct TYPE_4__ {void* deviceCap; void* blueToothOptions; void* rfSilent; void** regDmn; void* version; void* checksum; void* length; } ;
struct ar5416eeprom_4k {TYPE_3__ modalHeader; TYPE_1__ baseEepHeader; } ;
struct TYPE_5__ {void* spurChan; } ;
typedef  TYPE_3__ MODAL_EEP4K_HEADER ;

/* Variables and functions */
 size_t AR5416_4K_MAX_CHAINS ; 
 size_t AR5416_EEPROM_MODAL_SPURS ; 
 void* __bswap16 (void*) ; 
 size_t __bswap32 (size_t) ; 

__attribute__((used)) static void
eepromSwap(struct ar5416eeprom_4k *ee)
{
	uint32_t integer, i;
	uint16_t word;
	MODAL_EEP4K_HEADER *pModal;

	/* convert Base Eep header */
	word = __bswap16(ee->baseEepHeader.length);
	ee->baseEepHeader.length = word;

	word = __bswap16(ee->baseEepHeader.checksum);
	ee->baseEepHeader.checksum = word;

	word = __bswap16(ee->baseEepHeader.version);
	ee->baseEepHeader.version = word;

	word = __bswap16(ee->baseEepHeader.regDmn[0]);
	ee->baseEepHeader.regDmn[0] = word;

	word = __bswap16(ee->baseEepHeader.regDmn[1]);
	ee->baseEepHeader.regDmn[1] = word;

	word = __bswap16(ee->baseEepHeader.rfSilent);
	ee->baseEepHeader.rfSilent = word;

	word = __bswap16(ee->baseEepHeader.blueToothOptions);
	ee->baseEepHeader.blueToothOptions = word; 

	word = __bswap16(ee->baseEepHeader.deviceCap);
	ee->baseEepHeader.deviceCap = word;

	/* convert Modal Eep header */
	pModal = &ee->modalHeader;

	/* XXX linux/ah_osdep.h only defines __bswap32 for BE */
	integer = __bswap32(pModal->antCtrlCommon);
	pModal->antCtrlCommon = integer;

	for (i = 0; i < AR5416_4K_MAX_CHAINS; i++) {
		integer = __bswap32(pModal->antCtrlChain[i]);
		pModal->antCtrlChain[i] = integer;
	}

	for (i = 0; i < AR5416_EEPROM_MODAL_SPURS; i++) {
		word = __bswap16(pModal->spurChans[i].spurChan);
		pModal->spurChans[i].spurChan = word;
	}
}