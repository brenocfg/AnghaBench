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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 scalar_t__ use_dialog ; 
 scalar_t__ use_libdialog ; 

char *
dialog_prompt_lastline(char *prompt, uint8_t nlstate)
{
	uint8_t nls = nlstate; /* See dialog_prompt_nlstate() */
	char *lastline;
	char *p;

	if (prompt == NULL)
		return (NULL);
	if (*prompt == '\0')
		return (prompt); /* shortcut */

	lastline = p = prompt;
	while (*p != '\0') {
		/* dialog(1) and dialog(3) will render literal newlines */
		if (use_dialog || use_libdialog) {
			if (*p == '\n') {
				if (use_libdialog || !nls)
					lastline = p + 1;
				nls = FALSE; /* See declaration comment */
			}
		}
		/* dialog(3) does not expand escaped newlines */
		if (use_libdialog) {
			p++;
			continue;
		}
		if (*p == '\\' && *(p + 1) != '\0' && *(++p) == 'n') {
			nls = TRUE; /* See declaration comment */
			lastline = p + 1;
		}
		p++;
	}

	return (lastline);
}