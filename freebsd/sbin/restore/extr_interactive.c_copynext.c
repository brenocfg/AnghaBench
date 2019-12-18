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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static char *
copynext(char *input, char *output)
{
	char *cp, *bp;
	char quote;

	for (cp = input; *cp == ' ' || *cp == '\t'; cp++)
		/* skip to argument */;
	bp = output;
	while (*cp != ' ' && *cp != '\t' && *cp != '\0') {
		/*
		 * Handle back slashes.
		 */
		if (*cp == '\\') {
			if (*++cp == '\0') {
				fprintf(stderr,
					"command lines cannot be continued\n");
				continue;
			}
			*bp++ = *cp++;
			continue;
		}
		/*
		 * The usual unquoted case.
		 */
		if (*cp != '\'' && *cp != '"') {
			*bp++ = *cp++;
			continue;
		}
		/*
		 * Handle single and double quotes.
		 */
		quote = *cp++;
		while (*cp != quote && *cp != '\0')
			*bp++ = *cp++;
		if (*cp++ == '\0') {
			fprintf(stderr, "missing %c\n", quote);
			cp--;
			continue;
		}
	}
	*bp = '\0';
	return (cp);
}