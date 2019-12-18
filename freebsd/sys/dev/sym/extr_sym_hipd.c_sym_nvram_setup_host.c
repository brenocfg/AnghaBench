#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int host_id; } ;
struct TYPE_6__ {int flags; int host_id; int flags1; int flags2; } ;
struct TYPE_8__ {TYPE_2__ Tekram; TYPE_1__ Symbios; } ;
struct sym_nvram {int type; TYPE_3__ data; } ;
typedef  TYPE_4__* hcb_p ;
struct TYPE_9__ {int rv_scntl0; int myaddr; int verbose; int /*<<< orphan*/  usrflags; } ;

/* Variables and functions */
 int SYMBIOS_AVOID_BUS_RESET ; 
 int SYMBIOS_PARITY_ENABLE ; 
 int SYMBIOS_SCAN_HI_LO ; 
 int SYMBIOS_VERBOSE_MSGS ; 
 int /*<<< orphan*/  SYM_AVOID_BUS_RESET ; 
 int /*<<< orphan*/  SYM_SCAN_TARGETS_HILO ; 
#define  SYM_SYMBIOS_NVRAM 129 
#define  SYM_TEKRAM_NVRAM 128 

__attribute__((used)) static void sym_nvram_setup_host (hcb_p np, struct sym_nvram *nvram)
{
#ifdef SYM_CONF_NVRAM_SUPPORT
	/*
	 *  Get parity checking, host ID, verbose mode
	 *  and miscellaneous host flags from NVRAM.
	 */
	switch(nvram->type) {
	case SYM_SYMBIOS_NVRAM:
		if (!(nvram->data.Symbios.flags & SYMBIOS_PARITY_ENABLE))
			np->rv_scntl0  &= ~0x0a;
		np->myaddr = nvram->data.Symbios.host_id & 0x0f;
		if (nvram->data.Symbios.flags & SYMBIOS_VERBOSE_MSGS)
			np->verbose += 1;
		if (nvram->data.Symbios.flags1 & SYMBIOS_SCAN_HI_LO)
			np->usrflags |= SYM_SCAN_TARGETS_HILO;
		if (nvram->data.Symbios.flags2 & SYMBIOS_AVOID_BUS_RESET)
			np->usrflags |= SYM_AVOID_BUS_RESET;
		break;
	case SYM_TEKRAM_NVRAM:
		np->myaddr = nvram->data.Tekram.host_id & 0x0f;
		break;
	default:
		break;
	}
#endif
}