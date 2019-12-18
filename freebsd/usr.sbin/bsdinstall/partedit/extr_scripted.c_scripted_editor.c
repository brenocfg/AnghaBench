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
 int parse_disk_config (char*) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 char* strsep (char**,char*) ; 

int
scripted_editor(int argc, const char **argv)
{
	char *token;
	int i, error = 0, len = 0;

	for (i = 1; i < argc; i++)
		len += strlen(argv[i]) + 1;
	char inputbuf[len], *input = inputbuf;
	strcpy(input, argv[1]);
	for (i = 2; i < argc; i++) {
		strcat(input, " ");
		strcat(input, argv[i]);
	}

	while ((token = strsep(&input, ";")) != NULL) {
		error = parse_disk_config(token);
		if (error != 0)
			return (error);
	}

	return (0);
}