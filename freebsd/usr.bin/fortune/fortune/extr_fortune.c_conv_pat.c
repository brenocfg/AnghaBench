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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ isalpha (unsigned char) ; 
 scalar_t__ islower (unsigned char) ; 
 scalar_t__ isupper (unsigned char) ; 
 char* malloc (unsigned int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  tolower (unsigned char) ; 
 int /*<<< orphan*/  toupper (unsigned char) ; 

__attribute__((used)) static char *
conv_pat(char *orig)
{
	char		*sp;
	unsigned int	cnt;
	char		*new;

	cnt = 1;	/* allow for '\0' */
	for (sp = orig; *sp != '\0'; sp++)
		if (isalpha((unsigned char)*sp))
			cnt += 4;
		else
			cnt++;
	if ((new = malloc(cnt)) == NULL) {
		fprintf(stderr, "pattern too long for ignoring case\n");
		exit(1);
	}

	for (sp = new; *orig != '\0'; orig++) {
		if (islower((unsigned char)*orig)) {
			*sp++ = '[';
			*sp++ = *orig;
			*sp++ = toupper((unsigned char)*orig);
			*sp++ = ']';
		}
		else if (isupper((unsigned char)*orig)) {
			*sp++ = '[';
			*sp++ = *orig;
			*sp++ = tolower((unsigned char)*orig);
			*sp++ = ']';
		}
		else
			*sp++ = *orig;
	}
	*sp = '\0';

	return (new);
}