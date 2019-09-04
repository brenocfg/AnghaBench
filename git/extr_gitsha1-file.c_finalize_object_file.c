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
 int EEXIST ; 
 scalar_t__ OBJECT_CREATION_USES_RENAMES ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ adjust_shared_perm (char const*) ; 
 int errno ; 
 int error (int /*<<< orphan*/ ,char const*) ; 
 int error_errno (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ link (char const*,char const*) ; 
 scalar_t__ object_creation_mode ; 
 int /*<<< orphan*/  rename (char const*,char const*) ; 
 int /*<<< orphan*/  unlink_or_warn (char const*) ; 

int finalize_object_file(const char *tmpfile, const char *filename)
{
	int ret = 0;

	if (object_creation_mode == OBJECT_CREATION_USES_RENAMES)
		goto try_rename;
	else if (link(tmpfile, filename))
		ret = errno;

	/*
	 * Coda hack - coda doesn't like cross-directory links,
	 * so we fall back to a rename, which will mean that it
	 * won't be able to check collisions, but that's not a
	 * big deal.
	 *
	 * The same holds for FAT formatted media.
	 *
	 * When this succeeds, we just return.  We have nothing
	 * left to unlink.
	 */
	if (ret && ret != EEXIST) {
	try_rename:
		if (!rename(tmpfile, filename))
			goto out;
		ret = errno;
	}
	unlink_or_warn(tmpfile);
	if (ret) {
		if (ret != EEXIST) {
			return error_errno(_("unable to write file %s"), filename);
		}
		/* FIXME!!! Collision check here ? */
	}

out:
	if (adjust_shared_perm(filename))
		return error(_("unable to set permission to '%s'"), filename);
	return 0;
}