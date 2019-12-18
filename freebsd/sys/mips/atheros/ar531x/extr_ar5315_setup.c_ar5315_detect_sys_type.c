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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct ar531x_boarddata {scalar_t__ major; } ;

/* Variables and functions */
 int AR5312_REVISION_MAJOR (scalar_t__) ; 
#define  AR5312_REVISION_MAJ_AR2313 130 
#define  AR5312_REVISION_MAJ_AR5311 129 
#define  AR5312_REVISION_MAJ_AR5312 128 
 scalar_t__ AR5312_REVISION_MINOR (scalar_t__) ; 
 scalar_t__ AR5312_SYSREG_BASE ; 
 scalar_t__ AR5312_SYSREG_REVISION ; 
 scalar_t__ AR5315_CONFIG_BASE ; 
 scalar_t__ AR5315_CONFIG_END ; 
 scalar_t__ AR5315_SYSREG_BASE ; 
 scalar_t__ AR5315_SYSREG_SREV ; 
 scalar_t__ const AR531X_BD_MAGIC ; 
 int /*<<< orphan*/  AR531X_SOC_AR5311 ; 
 int /*<<< orphan*/  AR531X_SOC_AR5312 ; 
 int /*<<< orphan*/  AR531X_SOC_AR5313 ; 
 int /*<<< orphan*/  AR531X_SOC_AR5315 ; 
 int /*<<< orphan*/  AR531X_SOC_AR5316 ; 
 int /*<<< orphan*/  AR531X_SOC_AR5317 ; 
 int /*<<< orphan*/  AR531X_SOC_AR5318 ; 
 int AR_FIRST_GEN ; 
 int AR_SECOND_GEN ; 
 scalar_t__ ATH_READ_REG (scalar_t__) ; 
 scalar_t__ MIPS_PHYS_TO_KSEG1 (scalar_t__) ; 
 int /*<<< orphan*/  ar5312_chip_def ; 
 int /*<<< orphan*/  ar5315_chip_def ; 
 int /*<<< orphan*/ * ar5315_cpu_ops ; 
 int /*<<< orphan*/  ar5315_sys_type ; 
 int /*<<< orphan*/  ar531x_soc ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,scalar_t__) ; 

void
ar5315_detect_sys_type(void)
{
	char *chip = "????";
	uint32_t ver = 0;
	uint32_t rev = 0;
#if 0
	const uint8_t *ptr, *end;
	static const struct ar531x_boarddata *board = NULL;

	ptr = (const uint8_t *) MIPS_PHYS_TO_KSEG1(AR5315_CONFIG_END
		- 0x1000);

	end = (const uint8_t *)AR5315_CONFIG_BASE;

	for (; ptr > end; ptr -= 0x1000) {
		if (*(const uint32_t *)ptr == AR531X_BD_MAGIC) {
			board = (const struct ar531x_boarddata *) ptr;
			rev = board->major;
			break;
		}
	}
#endif
	int soctype;

#ifdef AR531X_1ST_GENERATION
	soctype = AR_FIRST_GEN;
#else
	soctype = AR_SECOND_GEN;
#endif

	if(soctype == AR_SECOND_GEN) {
		ar5315_cpu_ops = &ar5315_chip_def;

		ver = ATH_READ_REG(AR5315_SYSREG_BASE +
			AR5315_SYSREG_SREV);

		switch (ver) {
		case 0x86:
			ar531x_soc = AR531X_SOC_AR5315;
			chip = "2315";
			break;
		case 0x87:
			ar531x_soc = AR531X_SOC_AR5316;
			chip = "2316";
			break;
		case 0x90:
			ar531x_soc = AR531X_SOC_AR5317;
			chip = "2317";
			break;
		case 0x91:
			ar531x_soc = AR531X_SOC_AR5318;
			chip = "2318";
			break;
		}
	} else {
		ar5315_cpu_ops = &ar5312_chip_def;

		ver = ATH_READ_REG(AR5312_SYSREG_BASE +
			AR5312_SYSREG_REVISION);
		rev = AR5312_REVISION_MINOR(ver);

		switch (AR5312_REVISION_MAJOR(ver)) {
		case AR5312_REVISION_MAJ_AR5311:
			ar531x_soc = AR531X_SOC_AR5311;
			chip = "5311";
			break;
		case AR5312_REVISION_MAJ_AR5312:
			ar531x_soc = AR531X_SOC_AR5312;
			chip = "5312";
			break;
		case AR5312_REVISION_MAJ_AR2313:
			ar531x_soc = AR531X_SOC_AR5313;
			chip = "2313";
			break;
		}
	}

	sprintf(ar5315_sys_type, "Atheros AR%s rev %u", chip, rev);
}