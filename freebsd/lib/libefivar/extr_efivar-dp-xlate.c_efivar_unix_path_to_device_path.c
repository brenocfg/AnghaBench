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
struct gmesh {int dummy; } ;
typedef  int /*<<< orphan*/  efidp ;

/* Variables and functions */
 int EDOOFUS ; 
 int ENOMEM ; 
 int dev_path_to_dp (struct gmesh*,char*,int /*<<< orphan*/ *) ; 
 int efipart_to_dp (struct gmesh*,char*,int /*<<< orphan*/ *) ; 
 int errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  geom_deletetree (struct gmesh*) ; 
 scalar_t__ geom_gettree (struct gmesh*) ; 
 int path_to_dp (struct gmesh*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ strchr (char*,char) ; 
 char* strdup (char const*) ; 

int
efivar_unix_path_to_device_path(const char *path, efidp *dp)
{
	char *modpath = NULL, *cp;
	int rv = ENOMEM;
	struct gmesh mesh;

	/*
	 * Fail early for clearly bogus things
	 */
	if (path == NULL || dp == NULL)
		return (EDOOFUS);

	/*
	 * We'll need the goem mesh to grovel through it to find the
	 * efimedia attribute for any devices we find. Grab it here
	 * and release it to simplify the error paths out of the
	 * subordinate functions
	 */
	if (geom_gettree(&mesh))
		return (errno);

	/*
	 * Convert all \ to /. We'll convert them back again when
	 * we encode the file. Boot loaders are expected to cope.
	 */
	modpath = strdup(path);
	if (modpath == NULL)
		goto out;
	for (cp = modpath; *cp; cp++)
		if (*cp == '\\')
			*cp = '/';

	if (modpath[0] == '/' && modpath[1] == '/')	/* Handle //foo/bar/baz */
		rv = efipart_to_dp(&mesh, modpath, dp);
	else if (strchr(modpath, ':'))			/* Handle dev:/bar/baz */
		rv = dev_path_to_dp(&mesh, modpath, dp);
	else						/* Handle /a/b/c */
		rv = path_to_dp(&mesh, modpath, dp);

out:
	geom_deletetree(&mesh);
	free(modpath);

	return (rv);
}