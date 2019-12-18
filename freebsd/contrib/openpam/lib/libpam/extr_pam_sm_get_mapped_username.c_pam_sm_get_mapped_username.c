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
typedef  int /*<<< orphan*/  pam_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER () ; 
 int /*<<< orphan*/  PAM_SYSTEM_ERR ; 
 int /*<<< orphan*/  RETURNC (int /*<<< orphan*/ ) ; 

int
pam_sm_get_mapped_username(pam_handle_t *pamh,
	char *src_username,
	char *src_module_type,
	char *src_authn_domain,
	char *target_module_type,
	char *target_authn_domain,
	char **target_module_username,
	int argc,
	const char **argv)
{

	ENTER();
	RETURNC(PAM_SYSTEM_ERR);
}