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
typedef  char* efidp ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  asprintf (char**,char*,char const*,char*) ; 
 size_t efidp_parse_device_path (char*,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 char* path_to_file_dp (char*) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static int
build_dp(const char *efimedia, const char *relpath, efidp *dp)
{
	char *fp, *dptxt = NULL, *cp, *rp;
	int rv = 0;
	efidp out = NULL;
	size_t len;

	rp = strdup(relpath);
	for (cp = rp; *cp; cp++)
		if (*cp == '/')
			*cp = '\\';
	fp = path_to_file_dp(rp);
	free(rp);
	if (fp == NULL) {
		rv = ENOMEM;
		goto errout;
	}

	asprintf(&dptxt, "%s/%s", efimedia, fp);
	out = malloc(8192);
	len = efidp_parse_device_path(dptxt, out, 8192);
	if (len > 8192) {
		rv = ENOMEM;
		goto errout;
	}
	if (len == 0) {
		rv = EINVAL;
		goto errout;
	}

	*dp = out;
errout:
	if (rv) {
		free(out);
	}
	free(dptxt);
	free(fp);

	return rv;
}