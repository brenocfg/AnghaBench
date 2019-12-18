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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 char* fgetln (int /*<<< orphan*/ *,size_t*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 char* strdup (char*) ; 
 size_t strlen (char*) ; 

size_t
efgetln(FILE *fp, char **line)
{
	size_t rv;
	char *cp;

	cp = fgetln(fp, &rv);
	if (cp == NULL) {
		*line = NULL;
		return (rv);
	}
	if (cp[rv - 1] == '\n') {
		cp[rv - 1] = '\0';
		*line = strdup(cp);
		if (*line == NULL)
			errx(1, "cannot allocate memory");
		--rv;
	} else {
		*line = malloc(rv + 1);
		if (*line == NULL)
			errx(1, "cannot allocate memory");
		memcpy(*line, cp, rv);
		(*line)[rv] = '\0';
	}
	assert(rv == strlen(*line));
	return (rv);
}