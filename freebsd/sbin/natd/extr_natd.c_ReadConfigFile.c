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
 int /*<<< orphan*/  ParseOption (char*,char*) ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 char* fgetln (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 scalar_t__ isspace (char) ; 
 char* strchr (char*,char) ; 

void ReadConfigFile (const char* fileName)
{
	FILE*	file;
	char	*buf;
	size_t	len;
	char	*ptr, *p;
	char*	option;

	file = fopen (fileName, "r");
	if (!file)
		err(1, "cannot open config file %s", fileName);

	while ((buf = fgetln(file, &len)) != NULL) {
		if (buf[len - 1] == '\n')
			buf[len - 1] = '\0';
		else
			errx(1, "config file format error: "
				"last line should end with newline");

/*
 * Check for comments, strip off trailing spaces.
 */
		if ((ptr = strchr(buf, '#')))
			*ptr = '\0';
		for (ptr = buf; isspace(*ptr); ++ptr)
			continue;
		if (*ptr == '\0')
			continue;
		for (p = strchr(buf, '\0'); isspace(*--p);)
			continue;
		*++p = '\0';

/*
 * Extract option name.
 */
		option = ptr;
		while (*ptr && !isspace (*ptr))
			++ptr;

		if (*ptr != '\0') {

			*ptr = '\0';
			++ptr;
		}
/*
 * Skip white space between name and parms.
 */
		while (*ptr && isspace (*ptr))
			++ptr;

		ParseOption (option, *ptr ? ptr : NULL);
	}

	fclose (file);
}