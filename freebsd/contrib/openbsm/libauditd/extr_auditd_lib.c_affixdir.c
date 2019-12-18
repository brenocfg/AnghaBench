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
struct dir_ent {int /*<<< orphan*/  dirname; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ FILENAME_LEN ; 
 int /*<<< orphan*/  asprintf (char**,char*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  auditd_host ; 
 scalar_t__ auditd_hostlen ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static char *
affixdir(char *name, struct dir_ent *dirent)
{
	char *fn = NULL;

	/*
	 * Sanity check on file name.
	 */
	if (strlen(name) != FILENAME_LEN) {
		errno = EINVAL;
		return (NULL);
	}

	/*
	 * If the host is set then also add the hostname to the filename.
	 */
	if (auditd_hostlen > 0)
		asprintf(&fn, "%s/%s.%s", dirent->dirname, name, auditd_host);
	else
		asprintf(&fn, "%s/%s", dirent->dirname, name);
	return (fn);
}