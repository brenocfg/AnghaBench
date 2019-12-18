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
#define  EX_DATAERR 129 
 int /*<<< orphan*/  EX_OSERR ; 
#define  EX_UNAVAILABLE 128 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int ofwo_action (char*,char*) ; 
 char* strdup (char*) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  warnx (char*,char*,...) ; 

__attribute__((used)) static int
action(char *line)
{
	int rv;
	char *keyword, *arg;

	keyword = strdup(line);
	if (keyword == NULL)
		err(EX_OSERR, "malloc() failed");
	if ((arg = strrchr(keyword, '=')) != NULL)
		*arg++ = '\0';
	switch (rv = ofwo_action(keyword, arg)) {
		case EX_UNAVAILABLE:
			warnx("nothing available for '%s'.", keyword);
			break;
		case EX_DATAERR:
			warnx("invalid value '%s' for '%s'.", arg, keyword);
			break;
	}
	free(keyword);
	return(rv);
}