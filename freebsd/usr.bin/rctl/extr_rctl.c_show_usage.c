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
 scalar_t__ ENOSYS ; 
 scalar_t__ ERANGE ; 
 int RCTL_DEFAULT_BUFSIZE ; 
 int /*<<< orphan*/  enosys () ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 char* humanize_usage_amount (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int rctl_get_racct (char const*,scalar_t__,char*,size_t) ; 
 char* realloc (char*,size_t) ; 
 scalar_t__ strlen (char const*) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 

__attribute__((used)) static int
show_usage(const char *filter, const char *unexpanded_rule, int hflag)
{
	int error;
	char *copy, *outbuf = NULL, *tmp;
	size_t outbuflen = RCTL_DEFAULT_BUFSIZE / 4;

	for (;;) {
		outbuflen *= 4;
		outbuf = realloc(outbuf, outbuflen);
		if (outbuf == NULL)
			err(1, "realloc");
		error = rctl_get_racct(filter, strlen(filter) + 1,
		    outbuf, outbuflen);
		if (error == 0)
			break;
		if (errno == ERANGE)
			continue;
		if (errno == ENOSYS)
			enosys();
		warn("failed to show resource consumption for '%s'",
		    unexpanded_rule);
		free(outbuf);

		return (error);
	}

	copy = outbuf;
	while ((tmp = strsep(&copy, ",")) != NULL) {
		if (tmp[0] == '\0')
			break; /* XXX */

		if (hflag)
			tmp = humanize_usage_amount(tmp);

		printf("%s\n", tmp);
	}

	free(outbuf);

	return (error);
}