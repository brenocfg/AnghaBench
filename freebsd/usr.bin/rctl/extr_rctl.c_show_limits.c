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
 int /*<<< orphan*/  print_rules (char*,int,int) ; 
 int rctl_get_limits (char const*,scalar_t__,char*,size_t) ; 
 char* realloc (char*,size_t) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 

__attribute__((used)) static int
show_limits(const char *filter, const char *unexpanded_rule,
    int hflag, int nflag)
{
	int error;
	char *outbuf = NULL;
	size_t outbuflen = RCTL_DEFAULT_BUFSIZE / 4;

	for (;;) {
		outbuflen *= 4;
		outbuf = realloc(outbuf, outbuflen);
		if (outbuf == NULL)
			err(1, "realloc");
		error = rctl_get_limits(filter, strlen(filter) + 1,
		    outbuf, outbuflen);
		if (error == 0)
			break;
		if (errno == ERANGE)
			continue;
		if (errno == ENOSYS)
			enosys();
		warn("failed to get limits for '%s'", unexpanded_rule);
		free(outbuf);

		return (error);
	}

	print_rules(outbuf, hflag, nflag);
	free(outbuf);

	return (error);
}