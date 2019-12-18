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
struct req {char** p; int psz; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  MAN_DIR ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 char** mandoc_realloc (char**,int) ; 
 int /*<<< orphan*/  pg_error_internal () ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 int /*<<< orphan*/  validate_urifrag (char*) ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void
parse_manpath_conf(struct req *req)
{
	FILE	*fp;
	char	*dp;
	size_t	 dpsz;
	ssize_t	 len;

	if ((fp = fopen("manpath.conf", "r")) == NULL) {
		warn("%s/manpath.conf", MAN_DIR);
		pg_error_internal();
		exit(EXIT_FAILURE);
	}

	dp = NULL;
	dpsz = 0;

	while ((len = getline(&dp, &dpsz, fp)) != -1) {
		if (dp[len - 1] == '\n')
			dp[--len] = '\0';
		req->p = mandoc_realloc(req->p,
		    (req->psz + 1) * sizeof(char *));
		if ( ! validate_urifrag(dp)) {
			warnx("%s/manpath.conf contains "
			    "unsafe path \"%s\"", MAN_DIR, dp);
			pg_error_internal();
			exit(EXIT_FAILURE);
		}
		if (strchr(dp, '/') != NULL) {
			warnx("%s/manpath.conf contains "
			    "path with slash \"%s\"", MAN_DIR, dp);
			pg_error_internal();
			exit(EXIT_FAILURE);
		}
		req->p[req->psz++] = dp;
		dp = NULL;
		dpsz = 0;
	}
	free(dp);

	if (req->p == NULL) {
		warnx("%s/manpath.conf is empty", MAN_DIR);
		pg_error_internal();
		exit(EXIT_FAILURE);
	}
}