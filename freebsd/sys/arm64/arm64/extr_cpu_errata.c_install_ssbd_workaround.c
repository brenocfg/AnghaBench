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

/* Variables and functions */
 scalar_t__ PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCPU_SET (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int)) ; 
 int /*<<< orphan*/  SMCCC_ARCH_WORKAROUND_2 ; 
 scalar_t__ SMCCC_RET_SUCCESS ; 
#define  SSBD_FORCE_OFF 130 
#define  SSBD_FORCE_ON 129 
#define  SSBD_KERNEL 128 
 int /*<<< orphan*/  cpuid ; 
 char* kern_getenv (char*) ; 
 scalar_t__ smccc_arch_features (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smccc_arch_workaround_2 (int) ; 
 int /*<<< orphan*/  ssbd ; 
 int ssbd_method ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void
install_ssbd_workaround(void)
{
	char *env;

	if (PCPU_GET(cpuid) == 0) {
		env = kern_getenv("kern.cfg.ssbd");
		if (env != NULL) {
			if (strcmp(env, "force-on") == 0) {
				ssbd_method = SSBD_FORCE_ON;
			} else if (strcmp(env, "force-off") == 0) {
				ssbd_method = SSBD_FORCE_OFF;
			}
		}
	}

	/* Enable the workaround on this CPU if it's enabled in the firmware */
	if (smccc_arch_features(SMCCC_ARCH_WORKAROUND_2) != SMCCC_RET_SUCCESS)
		return;

	switch(ssbd_method) {
	case SSBD_FORCE_ON:
		smccc_arch_workaround_2(1);
		break;
	case SSBD_FORCE_OFF:
		smccc_arch_workaround_2(0);
		break;
	case SSBD_KERNEL:
	default:
		PCPU_SET(ssbd, smccc_arch_workaround_2);
		break;
	}
}