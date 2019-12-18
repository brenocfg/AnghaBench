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
 int parse_uri (char*,char const*,char**,char**,int*,char**) ; 

int
parse_ssh_uri(const char *uri, char **userp, char **hostp, int *portp)
{
	char *path;
	int r;

	r = parse_uri("ssh", uri, userp, hostp, portp, &path);
	if (r == 0 && path != NULL)
		r = -1;		/* path not allowed */
	return r;
}