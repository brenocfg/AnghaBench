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
 scalar_t__ fgetstr (char*,int,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strchr (char*,char) ; 
 char* strdup (char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int
help_getnext(int fd, char **topic, char **subtopic, char **desc)
{
	char	line[81], *cp, *ep;

	/* Make sure we provide sane values. */
	*topic = *subtopic = *desc = NULL;
	for (;;) {
		if (fgetstr(line, 80, fd) < 0)
			return (0);

		if (strlen(line) < 3 || line[0] != '#' || line[1] != ' ')
			continue;

		cp = line + 2;
		while (cp != NULL && *cp != 0) {
			ep = strchr(cp, ' ');
			if (*cp == 'T' && *topic == NULL) {
				if (ep != NULL)
					*ep++ = 0;
				*topic = strdup(cp + 1);
			} else if (*cp == 'S' && *subtopic == NULL) {
				if (ep != NULL)
					*ep++ = 0;
				*subtopic = strdup(cp + 1);
			} else if (*cp == 'D') {
				*desc = strdup(cp + 1);
				ep = NULL;
			}
			cp = ep;
		}
		if (*topic == NULL) {
			free(*subtopic);
			free(*desc);
			*subtopic = *desc = NULL;
			continue;
		}
		return (1);
	}
}