#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  lzh; } ;
typedef  TYPE_1__ libbe_handle_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int BE_ERR_INVALIDNAME ; 
 int BE_ERR_NOPOOL ; 
 int BE_ERR_SUCCESS ; 
 int BE_ERR_UNKNOWN ; 
 int BE_MAXPATHLEN ; 
 int /*<<< orphan*/  ENOTSUP ; 
#define  EZFS_INVALIDNAME 128 
 int be_exists (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  be_root_concat (TYPE_1__*,char const*,char*) ; 
 int /*<<< orphan*/  be_setup_snapshot_name (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  errno ; 
 int set_error (TYPE_1__*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char const*) ; 
 int strlcat (char*,char const*,int) ; 
 int strlcpy (char*,scalar_t__,int) ; 
 scalar_t__ strrchr (char*,char) ; 
 int zfs_snapshot (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 

int
be_snapshot(libbe_handle_t *lbh, const char *source, const char *snap_name,
    bool recursive, char *result)
{
	char buf[BE_MAXPATHLEN];
	int err;

	be_root_concat(lbh, source, buf);

	if ((err = be_exists(lbh, buf)) != 0)
		return (set_error(lbh, err));

	if (snap_name != NULL) {
		if (strlcat(buf, "@", sizeof(buf)) >= sizeof(buf))
			return (set_error(lbh, BE_ERR_INVALIDNAME));

		if (strlcat(buf, snap_name, sizeof(buf)) >= sizeof(buf))
			return (set_error(lbh, BE_ERR_INVALIDNAME));

		if (result != NULL)
			snprintf(result, BE_MAXPATHLEN, "%s@%s", source,
			    snap_name);
	} else {
		be_setup_snapshot_name(lbh, buf, sizeof(buf));

		if (result != NULL && strlcpy(result, strrchr(buf, '/') + 1,
		    sizeof(buf)) >= sizeof(buf))
			return (set_error(lbh, BE_ERR_INVALIDNAME));
	}
	if ((err = zfs_snapshot(lbh->lzh, buf, recursive, NULL)) != 0) {
		switch (err) {
		case EZFS_INVALIDNAME:
			return (set_error(lbh, BE_ERR_INVALIDNAME));

		default:
			/*
			 * The other errors that zfs_ioc_snapshot might return
			 * shouldn't happen if we've set things up properly, so
			 * we'll gloss over them and call it UNKNOWN as it will
			 * require further triage.
			 */
			if (errno == ENOTSUP)
				return (set_error(lbh, BE_ERR_NOPOOL));
			return (set_error(lbh, BE_ERR_UNKNOWN));
		}
	}

	return (BE_ERR_SUCCESS);
}