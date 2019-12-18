#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int ap_policy; int /*<<< orphan*/ * ap_str; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 TYPE_1__* au_polstr ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ *) ; 
 char* strdup (char const*) ; 
 char* strsep (char**,char*) ; 

int
au_strtopol(const char *polstr, int *policy)
{
	char *bufp, *string;
	char *buffer;
	int i, matched;

	*policy = 0;
	buffer = strdup(polstr);
	if (buffer == NULL)
		return (-1);

	bufp = buffer;
	while ((string = strsep(&bufp, ",")) != NULL) {
		matched = i = 0;

		do {
			if (strcmp(string, au_polstr[i].ap_str) == 0) {
				*policy |= au_polstr[i].ap_policy;
				matched = 1;
				break;
			}
		} while (NULL != au_polstr[++i].ap_str);

		if (!matched) {
			free(buffer);
			errno = EINVAL;
			return (-1);
		}
	}
	free(buffer);
	return (0);
}