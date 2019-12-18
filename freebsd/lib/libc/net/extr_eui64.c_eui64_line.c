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
struct eui64 {int dummy; } ;

/* Variables and functions */
 scalar_t__ eui64_aton (char*,struct eui64*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strdup (char const*) ; 
 size_t strlcpy (char*,char*,size_t) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int
eui64_line(const char *l, struct eui64 *e, char *hostname, size_t len)
{
	char *line, *linehead, *cur;

	linehead = strdup(l);
	if (linehead == NULL)
		return (-1);
	line = linehead;

	/* Find and parse the EUI64 */
	while ((cur = strsep(&line, " \t\r\n")) != NULL) {
		if (*cur != '\0') {
			if (eui64_aton(cur, e) == 0)
				break;
			else
				goto bad;
		}
	}

	/* Find the hostname */
	while ((cur = strsep(&line, " \t\r\n")) != NULL) {
		if (*cur != '\0') {
			if (strlcpy(hostname, cur, len) <= len)
				break;
			else
				goto bad;
		}
	}

	/* Make sure what remains is either whitespace or a comment */
	while ((cur = strsep(&line, " \t\r\n")) != NULL) {
		if (*cur == '#')
			break;
		if (*cur != '\0')
			goto bad;
	}

	free(linehead);
	return (0);

bad:
	free(linehead);
	return (-1);
}