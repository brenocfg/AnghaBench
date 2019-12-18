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
 int /*<<< orphan*/  err (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strdup (char const*) ; 
 char* strtok (char*,char*) ; 

__attribute__((used)) static int
specified_ro(const char *arg)
{
	char *optbuf, *opt;
	int ret = 0;

	optbuf = strdup(arg);
	if (optbuf == NULL)
		 err(1, NULL);

	for (opt = optbuf; (opt = strtok(opt, ",")) != NULL; opt = NULL) {
		if (strcmp(opt, "ro") == 0) {
			ret = 1;
			break;
		}
	}
	free(optbuf);
	return (ret);
}