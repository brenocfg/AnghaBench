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
 scalar_t__ strncmp (char const*,char*,int) ; 
 scalar_t__ use_dialog ; 
 scalar_t__ use_libdialog ; 

unsigned int
dialog_prompt_numlines(const char *prompt, uint8_t nlstate)
{
	uint8_t nls = nlstate; /* See dialog_prompt_nlstate() */
	const char *cp = prompt;
	unsigned int nlines = 1;

	if (prompt == NULL || *prompt == '\0')
		return (0);

	while (*cp != '\0') {
		if (use_dialog) {
			if (strncmp(cp, "\\n", 2) == 0) {
				cp++;
				nlines++;
				nls = TRUE; /* See declaration comment */
			} else if (*cp == '\n') {
				if (!nls)
					nlines++;
				nls = FALSE; /* See declaration comment */
			}
		} else if (use_libdialog) {
			if (*cp == '\n')
				nlines++;
		} else if (strncmp(cp, "\\n", 2) == 0) {
			cp++;
			nlines++;
		}
		cp++;
	}

	return (nlines);
}