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
 int /*<<< orphan*/  RL_PROMPT_END_IGNORE ; 
 char RL_PROMPT_START_IGNORE ; 
 int /*<<< orphan*/  el_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memmove (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/ * rl_prompt ; 
 char* strchr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 
 scalar_t__ strlen (char*) ; 

int
rl_set_prompt(const char *prompt)
{
	char *p;

	if (!prompt)
		prompt = "";
	if (rl_prompt != NULL && strcmp(rl_prompt, prompt) == 0)
		return 0;
	if (rl_prompt)
		el_free(rl_prompt);
	rl_prompt = strdup(prompt);
	if (rl_prompt == NULL)
		return -1;

	while ((p = strchr(rl_prompt, RL_PROMPT_END_IGNORE)) != NULL) {
		/* Remove adjacent end/start markers to avoid double-escapes. */
		if (p[1] == RL_PROMPT_START_IGNORE) {
			memmove(p, p + 2, 1 + strlen(p + 2));
		} else {
			*p = RL_PROMPT_START_IGNORE;
		}
	}

	return 0;
}