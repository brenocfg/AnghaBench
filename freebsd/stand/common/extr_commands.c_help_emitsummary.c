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
 int pager_output (char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int
help_emitsummary(char *topic, char *subtopic, char *desc)
{
	int	i;

	pager_output("    ");
	pager_output(topic);
	i = strlen(topic);
	if (subtopic != NULL) {
		pager_output(" ");
		pager_output(subtopic);
		i += strlen(subtopic) + 1;
	}
	if (desc != NULL) {
		do {
			pager_output(" ");
		} while (i++ < 30);
		pager_output(desc);
	}
	return (pager_output("\n"));
}