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
 int /*<<< orphan*/  FREE (char*) ; 
 int /*<<< orphan*/  PAM_PROMPT_ECHO_ON ; 
 int PAM_SUCCESS ; 
 int /*<<< orphan*/  PAM_USER ; 
 int /*<<< orphan*/  PAM_USER_PROMPT ; 
 int /*<<< orphan*/  RETURNC (int) ; 
 void* openpam_get_option (int /*<<< orphan*/ *,char*) ; 
 int openpam_subst (int /*<<< orphan*/ *,char*,size_t*,char const*) ; 
 int pam_get_item (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void const**) ; 
 int pam_prompt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**,char*,char const*) ; 
 int pam_set_item (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 char* user_prompt ; 

int
pam_get_user(pam_handle_t *pamh,
	const char **user,
	const char *prompt)
{
	char prompt_buf[1024];
	size_t prompt_size;
	const void *promptp;
	char *resp;
	int r;

	ENTER();
	r = pam_get_item(pamh, PAM_USER, (const void **)user);
	if (r == PAM_SUCCESS && *user != NULL)
		RETURNC(PAM_SUCCESS);
	/* pam policy overrides the module's choice */
	if ((promptp = openpam_get_option(pamh, "user_prompt")) != NULL)
		prompt = promptp;
	/* no prompt provided, see if there is one tucked away somewhere */
	if (prompt == NULL) {
		r = pam_get_item(pamh, PAM_USER_PROMPT, &promptp);
		if (r == PAM_SUCCESS && promptp != NULL)
			prompt = promptp;
	}
	/* fall back to hardcoded default */
	if (prompt == NULL)
		prompt = user_prompt;
	/* expand */
	prompt_size = sizeof prompt_buf;
	r = openpam_subst(pamh, prompt_buf, &prompt_size, prompt);
	if (r == PAM_SUCCESS && prompt_size <= sizeof prompt_buf)
		prompt = prompt_buf;
	r = pam_prompt(pamh, PAM_PROMPT_ECHO_ON, &resp, "%s", prompt);
	if (r != PAM_SUCCESS)
		RETURNC(r);
	r = pam_set_item(pamh, PAM_USER, resp);
	FREE(resp);
	if (r != PAM_SUCCESS)
		RETURNC(r);
	r = pam_get_item(pamh, PAM_USER, (const void **)user);
	RETURNC(r);
}