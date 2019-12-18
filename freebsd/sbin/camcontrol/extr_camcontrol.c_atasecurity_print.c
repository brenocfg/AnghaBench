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
struct ata_params {int security_status; int master_passwd_revision; int /*<<< orphan*/  enhanced_erase_time; int /*<<< orphan*/  erase_time; } ;

/* Variables and functions */
 int ATA_SECURITY_COUNT_EXP ; 
 int ATA_SECURITY_ENABLED ; 
 int ATA_SECURITY_ENH_SUPP ; 
 int ATA_SECURITY_FROZEN ; 
 int ATA_SECURITY_LEVEL ; 
 int ATA_SECURITY_LOCKED ; 
 int ATA_SECURITY_SUPPORTED ; 
 int CAM_ARG_VERBOSE ; 
 int arglist ; 
 int /*<<< orphan*/  atasecurity_print_time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
atasecurity_print(struct ata_params *parm)
{

	printf("\nSecurity Option           Value\n");
	if (arglist & CAM_ARG_VERBOSE) {
		printf("status                    %04x\n",
		       parm->security_status);
	}
	printf("supported                 %s\n",
		parm->security_status & ATA_SECURITY_SUPPORTED ? "yes" : "no");
	if (!(parm->security_status & ATA_SECURITY_SUPPORTED))
		return;
	printf("enabled                   %s\n",
		parm->security_status & ATA_SECURITY_ENABLED ? "yes" : "no");
	printf("drive locked              %s\n",
		parm->security_status & ATA_SECURITY_LOCKED ? "yes" : "no");
	printf("security config frozen    %s\n",
		parm->security_status & ATA_SECURITY_FROZEN ? "yes" : "no");
	printf("count expired             %s\n",
		parm->security_status & ATA_SECURITY_COUNT_EXP ? "yes" : "no");
	printf("security level            %s\n",
		parm->security_status & ATA_SECURITY_LEVEL ? "maximum" : "high");
	printf("enhanced erase supported  %s\n",
		parm->security_status & ATA_SECURITY_ENH_SUPP ? "yes" : "no");
	printf("erase time                ");
	atasecurity_print_time(parm->erase_time);
	printf("\n");
	printf("enhanced erase time       ");
	atasecurity_print_time(parm->enhanced_erase_time);
	printf("\n");
	printf("master password rev       %04x%s\n",
		parm->master_passwd_revision,
		parm->master_passwd_revision == 0x0000 ||
		parm->master_passwd_revision == 0xFFFF ?  " (unsupported)" : "");
}