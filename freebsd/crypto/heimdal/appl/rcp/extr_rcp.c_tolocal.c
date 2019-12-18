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
struct TYPE_2__ {char* pw_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  _PATH_CP ; 
 int asprintf (char**,char*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  cmd ; 
 char* colon (char*) ; 
 scalar_t__ do_cmd (char*,char*,char*,int*,int*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errs ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ iamrecursive ; 
 int /*<<< orphan*/  okname (char*) ; 
 scalar_t__ pflag ; 
 TYPE_1__* pwd ; 
 int remin ; 
 int remout ; 
 int /*<<< orphan*/  sink (int,char**) ; 
 char* strchr (char*,char) ; 
 scalar_t__ susystem (char*) ; 

void
tolocal(int argc, char **argv)
{
	int i;
	char *bp, *host, *src, *suser;

	for (i = 0; i < argc - 1; i++) {
		int ret;

		if (!(src = colon(argv[i]))) {		/* Local to local. */
			ret = asprintf(&bp, "exec %s%s%s %s %s", _PATH_CP,
			    iamrecursive ? " -PR" : "", pflag ? " -p" : "",
			    argv[i], argv[argc - 1]);
			if (ret == -1)
				err (1, "malloc");
			if (susystem(bp))
				++errs;
			free(bp);
			continue;
		}
		*src++ = 0;
		if (*src == 0)
			src = ".";
		if ((host = strchr(argv[i], '@')) == NULL) {
			host = argv[i];
			suser = pwd->pw_name;
		} else {
			*host++ = 0;
			suser = argv[i];
			if (*suser == '\0')
				suser = pwd->pw_name;
			else if (!okname(suser))
				continue;
		}
		ret = asprintf(&bp, "%s -f %s", cmd, src);
		if (ret == -1)
			err (1, "malloc");
		if (do_cmd(host, suser, bp, &remin, &remout) < 0) {
			free(bp);
			++errs;
			continue;
		}
		free(bp);
		sink(1, argv + argc - 1);
		close(remin);
		remin = remout = -1;
	}
}