#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * list; } ;
typedef  TYPE_1__ arglist ;
typedef  int /*<<< orphan*/  alist ;

/* Variables and functions */
 char* _PATH_CP ; 
 int /*<<< orphan*/  addargs (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  cmd ; 
 scalar_t__ do_cmd (char*,char*,int,char*,int*,int*) ; 
 scalar_t__ do_local_cmd (TYPE_1__*) ; 
 int /*<<< orphan*/  errs ; 
 int /*<<< orphan*/  fmprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  freeargs (TYPE_1__*) ; 
 scalar_t__ iamrecursive ; 
 int /*<<< orphan*/  memset (TYPE_1__*,char,int) ; 
 int /*<<< orphan*/  okname (char*) ; 
 int parse_scp_uri (char*,char**,char**,int*,char**) ; 
 int /*<<< orphan*/  parse_user_host_path (char*,char**,char**,char**) ; 
 scalar_t__ pflag ; 
 int remin ; 
 int remout ; 
 int /*<<< orphan*/  sink (int,char**,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  xasprintf (char**,char*,int /*<<< orphan*/ ,char*,char*) ; 

void
tolocal(int argc, char **argv)
{
	char *bp, *host = NULL, *src = NULL, *suser = NULL;
	arglist alist;
	int i, r, sport = -1;

	memset(&alist, '\0', sizeof(alist));
	alist.list = NULL;

	for (i = 0; i < argc - 1; i++) {
		free(suser);
		free(host);
		free(src);
		r = parse_scp_uri(argv[i], &suser, &host, &sport, &src);
		if (r == -1) {
			fmprintf(stderr, "%s: invalid uri\n", argv[i]);
			++errs;
			continue;
		}
		if (r != 0)
			parse_user_host_path(argv[i], &suser, &host, &src);
		if (suser != NULL && !okname(suser)) {
			++errs;
			continue;
		}
		if (!host) {	/* Local to local. */
			freeargs(&alist);
			addargs(&alist, "%s", _PATH_CP);
			if (iamrecursive)
				addargs(&alist, "-r");
			if (pflag)
				addargs(&alist, "-p");
			addargs(&alist, "--");
			addargs(&alist, "%s", argv[i]);
			addargs(&alist, "%s", argv[argc-1]);
			if (do_local_cmd(&alist))
				++errs;
			continue;
		}
		/* Remote to local. */
		xasprintf(&bp, "%s -f %s%s",
		    cmd, *src == '-' ? "-- " : "", src);
		if (do_cmd(host, suser, sport, bp, &remin, &remout) < 0) {
			free(bp);
			++errs;
			continue;
		}
		free(bp);
		sink(1, argv + argc - 1, src);
		(void) close(remin);
		remin = remout = -1;
	}
	free(suser);
	free(host);
	free(src);
}