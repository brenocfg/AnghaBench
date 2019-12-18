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
 int FALSE ; 
 int TRUE ; 
 scalar_t__ use_color ; 
 scalar_t__ use_dialog ; 
 scalar_t__ use_libdialog ; 

unsigned int
dialog_prompt_longestline(const char *prompt, uint8_t nlstate)
{
	uint8_t backslash = 0;
	uint8_t nls = nlstate; /* See dialog_prompt_nlstate() */
	const char *p = prompt;
	int longest = 0;
	int n = 0;

	/* `prompt' parameter is required */
	if (prompt == NULL)
		return (0);
	if (*prompt == '\0')
		return (0); /* shortcut */

	/* Loop until the end of the string */
	while (*p != '\0') {
		/* dialog(1) and dialog(3) will render literal newlines */
		if (use_dialog || use_libdialog) {
			if (*p == '\n') {
				if (!use_libdialog && nls)
					n++;
				else {
					if (n > longest)
						longest = n;
					n = 0;
				}
				nls = FALSE; /* See declaration comment */
				p++;
				continue;
			}
		}

		/* Check for backslash character */
		if (*p == '\\') {
			/* If second backslash, count as a single-char */
			if ((backslash ^= 1) == 0)
				n++;
		} else if (backslash) {
			if (*p == 'n' && !use_libdialog) { /* new line */
				/* NB: dialog(3) ignores escaped newlines */
				nls = TRUE; /* See declaration comment */
				if (n > longest)
					longest = n;
				n = 0;
			} else if (use_color && *p == 'Z') {
				if (*++p != '\0')
					p++;
				backslash = 0;
				continue;
			} else /* [X]dialog(1)/dialog(3) only expand those */
				n += 2;

			backslash = 0;
		} else
			n++;
		p++;
	}
	if (n > longest)
		longest = n;

	return (longest);
}