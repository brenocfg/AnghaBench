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
#define  PAM_AUTHTOK 129 
 int PAM_AUTHTOK_PROMPT ; 
 int PAM_AUTH_ERR ; 
 int PAM_BAD_CONSTANT ; 
 int PAM_HOST ; 
 int /*<<< orphan*/  PAM_MAX_RESP_SIZE ; 
#define  PAM_OLDAUTHTOK 128 
 int PAM_OLDAUTHTOK_PROMPT ; 
 int PAM_PROMPT_ECHO_OFF ; 
 int PAM_PROMPT_ECHO_ON ; 
 int PAM_RHOST ; 
 int PAM_SUCCESS ; 
 int PAM_TRY_AGAIN ; 
 int /*<<< orphan*/  RETURNC (int) ; 
 char* authtok_prompt ; 
 char* authtok_prompt_remote ; 
 char* newauthtok_prompt ; 
 char* oldauthtok_prompt ; 
 void* openpam_get_option (int /*<<< orphan*/ *,char const*) ; 
 int openpam_subst (int /*<<< orphan*/ *,char*,size_t*,char const*) ; 
 int pam_get_item (int /*<<< orphan*/ *,int,void const**) ; 
 int pam_prompt (int /*<<< orphan*/ *,int,char**,char*,char const*) ; 
 int pam_set_item (int /*<<< orphan*/ *,int,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
pam_get_authtok(pam_handle_t *pamh,
	int item,
	const char **authtok,
	const char *prompt)
{
	char prompt_buf[1024];
	size_t prompt_size;
	const void *oldauthtok, *prevauthtok, *promptp;
	const char *prompt_option, *default_prompt;
	const void *lhost, *rhost;
	char *resp, *resp2;
	int pitem, r, style, twice;

	ENTER();
	*authtok = NULL;
	twice = 0;
	switch (item) {
	case PAM_AUTHTOK:
		pitem = PAM_AUTHTOK_PROMPT;
		prompt_option = "authtok_prompt";
		default_prompt = authtok_prompt;
		r = pam_get_item(pamh, PAM_RHOST, &rhost);
		if (r == PAM_SUCCESS && rhost != NULL) {
			r = pam_get_item(pamh, PAM_HOST, &lhost);
			if (r == PAM_SUCCESS && lhost != NULL) {
				if (strcmp(rhost, lhost) != 0)
					default_prompt = authtok_prompt_remote;
			}
		}
		r = pam_get_item(pamh, PAM_OLDAUTHTOK, &oldauthtok);
		if (r == PAM_SUCCESS && oldauthtok != NULL) {
			default_prompt = newauthtok_prompt;
			twice = 1;
		}
		break;
	case PAM_OLDAUTHTOK:
		pitem = PAM_OLDAUTHTOK_PROMPT;
		prompt_option = "oldauthtok_prompt";
		default_prompt = oldauthtok_prompt;
		twice = 0;
		break;
	default:
		RETURNC(PAM_BAD_CONSTANT);
	}
	if (openpam_get_option(pamh, "try_first_pass") ||
	    openpam_get_option(pamh, "use_first_pass")) {
		r = pam_get_item(pamh, item, &prevauthtok);
		if (r == PAM_SUCCESS && prevauthtok != NULL) {
			*authtok = prevauthtok;
			RETURNC(PAM_SUCCESS);
		} else if (openpam_get_option(pamh, "use_first_pass")) {
			RETURNC(r == PAM_SUCCESS ? PAM_AUTH_ERR : r);
		}
	}
	/* pam policy overrides the module's choice */
	if ((promptp = openpam_get_option(pamh, prompt_option)) != NULL)
		prompt = promptp;
	/* no prompt provided, see if there is one tucked away somewhere */
	if (prompt == NULL) {
		r = pam_get_item(pamh, pitem, &promptp);
		if (r == PAM_SUCCESS && promptp != NULL)
			prompt = promptp;
	}
	/* fall back to hardcoded default */
	if (prompt == NULL)
		prompt = default_prompt;
	/* expand */
	prompt_size = sizeof prompt_buf;
	r = openpam_subst(pamh, prompt_buf, &prompt_size, prompt);
	if (r == PAM_SUCCESS && prompt_size <= sizeof prompt_buf)
		prompt = prompt_buf;
	style = openpam_get_option(pamh, "echo_pass") ?
	    PAM_PROMPT_ECHO_ON : PAM_PROMPT_ECHO_OFF;
	r = pam_prompt(pamh, style, &resp, "%s", prompt);
	if (r != PAM_SUCCESS)
		RETURNC(r);
	if (twice) {
		r = pam_prompt(pamh, style, &resp2, "Retype %s", prompt);
		if (r != PAM_SUCCESS) {
			strlset(resp, 0, PAM_MAX_RESP_SIZE);
			FREE(resp);
			RETURNC(r);
		}
		if (strcmp(resp, resp2) != 0) {
			strlset(resp, 0, PAM_MAX_RESP_SIZE);
			FREE(resp);
		}
		strlset(resp2, 0, PAM_MAX_RESP_SIZE);
		FREE(resp2);
	}
	if (resp == NULL)
		RETURNC(PAM_TRY_AGAIN);
	r = pam_set_item(pamh, item, resp);
	strlset(resp, 0, PAM_MAX_RESP_SIZE);
	FREE(resp);
	if (r != PAM_SUCCESS)
		RETURNC(r);
	r = pam_get_item(pamh, item, (const void **)authtok);
	RETURNC(r);
}