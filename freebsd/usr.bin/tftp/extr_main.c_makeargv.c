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
 int MAX_MARGV ; 
 scalar_t__ isspace (char) ; 
 int margc ; 
 char** margv ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static void
makeargv(char *line)
{
	char *cp;
	char **argp = margv;

	margc = 0;
	if ((cp = strchr(line, '\n')) != NULL)
		*cp = '\0';
	for (cp = line; margc < MAX_MARGV - 1 && *cp != '\0';) {
		while (isspace(*cp))
			cp++;
		if (*cp == '\0')
			break;
		*argp++ = cp;
		margc += 1;
		while (*cp != '\0' && !isspace(*cp))
			cp++;
		if (*cp == '\0')
			break;
		*cp++ = '\0';
	}
	*argp++ = 0;
}