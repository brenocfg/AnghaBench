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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int FALSE ; 
 int MAX_TEMPSTR ; 
 int TRUE ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int
in_file(char *string, FILE *file)
{
	char line[MAX_TEMPSTR];

	rewind(file);
	while (fgets(line, MAX_TEMPSTR, file)) {
		if (line[0] != '\0')
			if (line[strlen(line)-1] == '\n')
				line[strlen(line)-1] = '\0';
		if (0 == strcmp(line, string))
			return TRUE;
	}
	return FALSE;
}