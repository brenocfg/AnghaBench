#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int nr; TYPE_1__* items; } ;
struct merge_options {TYPE_2__ df_conflict_file_set; } ;
struct TYPE_3__ {char* string; } ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int SCLD_EXISTS ; 
 char* _ (char*) ; 
 int err (struct merge_options*,char const*,char const*,...) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  output (struct merge_options*,int,char*,char const*) ; 
 int safe_create_leading_directories_const (char const*) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,size_t) ; 
 int /*<<< orphan*/  unlink (char const*) ; 
 int /*<<< orphan*/  unsorted_string_list_delete_item (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ would_lose_untracked (struct merge_options*,char const*) ; 

__attribute__((used)) static int make_room_for_path(struct merge_options *o, const char *path)
{
	int status, i;
	const char *msg = _("failed to create path '%s'%s");

	/* Unlink any D/F conflict files that are in the way */
	for (i = 0; i < o->df_conflict_file_set.nr; i++) {
		const char *df_path = o->df_conflict_file_set.items[i].string;
		size_t pathlen = strlen(path);
		size_t df_pathlen = strlen(df_path);
		if (df_pathlen < pathlen &&
		    path[df_pathlen] == '/' &&
		    strncmp(path, df_path, df_pathlen) == 0) {
			output(o, 3,
			       _("Removing %s to make room for subdirectory\n"),
			       df_path);
			unlink(df_path);
			unsorted_string_list_delete_item(&o->df_conflict_file_set,
							 i, 0);
			break;
		}
	}

	/* Make sure leading directories are created */
	status = safe_create_leading_directories_const(path);
	if (status) {
		if (status == SCLD_EXISTS)
			/* something else exists */
			return err(o, msg, path, _(": perhaps a D/F conflict?"));
		return err(o, msg, path, "");
	}

	/*
	 * Do not unlink a file in the work tree if we are not
	 * tracking it.
	 */
	if (would_lose_untracked(o, path))
		return err(o, _("refusing to lose untracked file at '%s'"),
			   path);

	/* Successful unlink is good.. */
	if (!unlink(path))
		return 0;
	/* .. and so is no existing file */
	if (errno == ENOENT)
		return 0;
	/* .. but not some other error (who really cares what?) */
	return err(o, msg, path, _(": perhaps a D/F conflict?"));
}