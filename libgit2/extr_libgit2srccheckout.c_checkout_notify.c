#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wdfile ;
struct TYPE_14__ {char* path; int /*<<< orphan*/  mode; int /*<<< orphan*/  file_size; int /*<<< orphan*/  id; } ;
typedef  TYPE_2__ git_index_entry ;
struct TYPE_15__ {char* path; int /*<<< orphan*/  mode; int /*<<< orphan*/  flags; int /*<<< orphan*/  size; int /*<<< orphan*/  id; } ;
typedef  TYPE_3__ git_diff_file ;
struct TYPE_16__ {int status; TYPE_3__ old_file; TYPE_3__ new_file; } ;
typedef  TYPE_4__ git_diff_delta ;
typedef  int git_checkout_notify_t ;
struct TYPE_13__ {int (* notify_cb ) (int,char const*,TYPE_3__ const*,TYPE_3__ const*,TYPE_3__ const*,int /*<<< orphan*/ ) ;int notify_flags; int /*<<< orphan*/  notify_payload; } ;
struct TYPE_17__ {TYPE_1__ opts; } ;
typedef  TYPE_5__ checkout_data ;

/* Variables and functions */
#define  GIT_DELTA_ADDED 135 
#define  GIT_DELTA_DELETED 134 
#define  GIT_DELTA_IGNORED 133 
#define  GIT_DELTA_MODIFIED 132 
#define  GIT_DELTA_TYPECHANGE 131 
#define  GIT_DELTA_UNMODIFIED 130 
#define  GIT_DELTA_UNREADABLE 129 
#define  GIT_DELTA_UNTRACKED 128 
 int /*<<< orphan*/  GIT_DIFF_FLAG_VALID_ID ; 
 int git_error_set_after_callback_function (int,char*) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int stub1 (int,char const*,TYPE_3__ const*,TYPE_3__ const*,TYPE_3__ const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int checkout_notify(
	checkout_data *data,
	git_checkout_notify_t why,
	const git_diff_delta *delta,
	const git_index_entry *wditem)
{
	git_diff_file wdfile;
	const git_diff_file *baseline = NULL, *target = NULL, *workdir = NULL;
	const char *path = NULL;

	if (!data->opts.notify_cb ||
		(why & data->opts.notify_flags) == 0)
		return 0;

	if (wditem) {
		memset(&wdfile, 0, sizeof(wdfile));

		git_oid_cpy(&wdfile.id, &wditem->id);
		wdfile.path = wditem->path;
		wdfile.size = wditem->file_size;
		wdfile.flags = GIT_DIFF_FLAG_VALID_ID;
		wdfile.mode = wditem->mode;

		workdir = &wdfile;

		path = wditem->path;
	}

	if (delta) {
		switch (delta->status) {
		case GIT_DELTA_UNMODIFIED:
		case GIT_DELTA_MODIFIED:
		case GIT_DELTA_TYPECHANGE:
		default:
			baseline = &delta->old_file;
			target = &delta->new_file;
			break;
		case GIT_DELTA_ADDED:
		case GIT_DELTA_IGNORED:
		case GIT_DELTA_UNTRACKED:
		case GIT_DELTA_UNREADABLE:
			target = &delta->new_file;
			break;
		case GIT_DELTA_DELETED:
			baseline = &delta->old_file;
			break;
		}

		path = delta->old_file.path;
	}

	{
		int error = data->opts.notify_cb(
			why, path, baseline, target, workdir, data->opts.notify_payload);

		return git_error_set_after_callback_function(
			error, "git_checkout notification");
	}
}