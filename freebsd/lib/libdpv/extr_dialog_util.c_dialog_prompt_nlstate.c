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
typedef  int uint8_t ;

/* Variables and functions */
 int strlen (char const*) ; 

uint8_t
dialog_prompt_nlstate(const char *prompt)
{
	const char *cp;

	if (prompt == NULL)
		return 0;

	/*
	 * Work our way backward from the end of the string for efficiency.
	 */
	cp = prompt + strlen(prompt);
	while (--cp >= prompt) {
		/*
		 * If we get to a literal newline first, this prompt ends in a
		 * clean state for rendering with dialog(1). Otherwise, if we
		 * get to an escaped newline first, this prompt ends in an un-
		 * clean state (following literal will be mangled; see above).
		 */
		if (*cp == '\n')
			return (0);
		else if (*cp == 'n' && --cp > prompt && *cp == '\\')
			return (1);
	}

	return (0); /* no newlines (escaped or otherwise) */
}