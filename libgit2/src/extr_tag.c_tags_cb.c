#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int (* cb ) (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  cb_data; int /*<<< orphan*/  repo; } ;
typedef  TYPE_1__ tag_cb_data ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_REFS_TAGS_DIR ; 
 scalar_t__ git__prefixcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_error_set_after_callback_function (int,char*) ; 
 int git_reference_name_to_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int stub1 (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tags_cb(const char *ref, void *data)
{
	int error;
	git_oid oid;
	tag_cb_data *d = (tag_cb_data *)data;

	if (git__prefixcmp(ref, GIT_REFS_TAGS_DIR) != 0)
		return 0; /* no tag */

	if (!(error = git_reference_name_to_id(&oid, d->repo, ref))) {
		if ((error = d->cb(ref, &oid, d->cb_data)) != 0)
			git_error_set_after_callback_function(error, "git_tag_foreach");
	}

	return error;
}