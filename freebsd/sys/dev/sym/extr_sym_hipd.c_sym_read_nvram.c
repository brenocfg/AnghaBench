#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  Tekram; int /*<<< orphan*/  Symbios; } ;
struct sym_nvram {int type; TYPE_1__ data; } ;
typedef  int /*<<< orphan*/  hcb_p ;

/* Variables and functions */
 scalar_t__ SYM_SETUP_SYMBIOS_NVRAM ; 
 scalar_t__ SYM_SETUP_TEKRAM_NVRAM ; 
 int SYM_SYMBIOS_NVRAM ; 
 int SYM_TEKRAM_NVRAM ; 
 int /*<<< orphan*/  sym_display_Symbios_nvram (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sym_display_Tekram_nvram (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sym_read_Symbios_nvram (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sym_read_Tekram_nvram (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sym_read_nvram(hcb_p np, struct sym_nvram *nvp)
{
#ifdef SYM_CONF_NVRAM_SUPPORT
	/*
	 *  Try to read SYMBIOS nvram.
	 *  Try to read TEKRAM nvram if Symbios nvram not found.
	 */
	if	(SYM_SETUP_SYMBIOS_NVRAM &&
		 !sym_read_Symbios_nvram (np, &nvp->data.Symbios)) {
		nvp->type = SYM_SYMBIOS_NVRAM;
#ifdef SYM_CONF_DEBUG_NVRAM
		sym_display_Symbios_nvram(np, &nvp->data.Symbios);
#endif
	}
	else if	(SYM_SETUP_TEKRAM_NVRAM &&
		 !sym_read_Tekram_nvram (np, &nvp->data.Tekram)) {
		nvp->type = SYM_TEKRAM_NVRAM;
#ifdef SYM_CONF_DEBUG_NVRAM
		sym_display_Tekram_nvram(np, &nvp->data.Tekram);
#endif
	}
	else
		nvp->type = 0;
#else
	nvp->type = 0;
#endif
	return nvp->type;
}