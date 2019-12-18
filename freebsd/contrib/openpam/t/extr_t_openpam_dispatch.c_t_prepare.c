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
 int /*<<< orphan*/  OPENPAM_FALLBACK_TO_OTHER ; 
 int /*<<< orphan*/  OPENPAM_RESTRICT_MODULE_NAME ; 
 int /*<<< orphan*/  OPENPAM_RESTRICT_SERVICE_NAME ; 
 int /*<<< orphan*/  OPENPAM_VERIFY_MODULE_FILE ; 
 int /*<<< orphan*/  OPENPAM_VERIFY_POLICY_FILE ; 
 int /*<<< orphan*/  T (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  empty_policy ; 
 int /*<<< orphan*/ * getenv (char*) ; 
 int /*<<< orphan*/  mod_return ; 
 int /*<<< orphan*/  openpam_set_feature (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pam_return_so ; 
 int /*<<< orphan*/  t_printv (char*) ; 

__attribute__((used)) static int
t_prepare(int argc, char *argv[])
{

	(void)argc;
	(void)argv;

	if ((pam_return_so = getenv("PAM_RETURN_SO")) == NULL) {
		t_printv("define PAM_RETURN_SO before running these tests\n");
		return (0);
	}

	openpam_set_feature(OPENPAM_RESTRICT_MODULE_NAME, 0);
	openpam_set_feature(OPENPAM_VERIFY_MODULE_FILE, 0);
	openpam_set_feature(OPENPAM_RESTRICT_SERVICE_NAME, 0);
	openpam_set_feature(OPENPAM_VERIFY_POLICY_FILE, 0);
	openpam_set_feature(OPENPAM_FALLBACK_TO_OTHER, 0);

	T(empty_policy);
	T(mod_return);

	return (0);
}