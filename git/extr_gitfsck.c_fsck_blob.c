#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fsck_options {int dummy; } ;
struct fsck_gitmodules_data {int ret; struct fsck_options* options; TYPE_1__* obj; } ;
struct config_options {int /*<<< orphan*/  error_action; int /*<<< orphan*/  member_0; } ;
struct TYPE_3__ {int /*<<< orphan*/  oid; } ;
struct blob {TYPE_1__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_ERROR_SILENT ; 
 int /*<<< orphan*/  CONFIG_ORIGIN_BLOB ; 
 int /*<<< orphan*/  FSCK_MSG_GITMODULES_LARGE ; 
 int /*<<< orphan*/  FSCK_MSG_GITMODULES_PARSE ; 
 int /*<<< orphan*/  fsck_gitmodules_fn ; 
 scalar_t__ git_config_from_mem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*,unsigned long,struct fsck_gitmodules_data*,struct config_options*) ; 
 int /*<<< orphan*/  gitmodules_done ; 
 int /*<<< orphan*/  gitmodules_found ; 
 scalar_t__ object_on_skiplist (struct fsck_options*,TYPE_1__*) ; 
 int /*<<< orphan*/  oidset_contains (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oidset_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int report (struct fsck_options*,TYPE_1__*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int fsck_blob(struct blob *blob, const char *buf,
		     unsigned long size, struct fsck_options *options)
{
	struct fsck_gitmodules_data data;
	struct config_options config_opts = { 0 };

	if (!oidset_contains(&gitmodules_found, &blob->object.oid))
		return 0;
	oidset_insert(&gitmodules_done, &blob->object.oid);

	if (object_on_skiplist(options, &blob->object))
		return 0;

	if (!buf) {
		/*
		 * A missing buffer here is a sign that the caller found the
		 * blob too gigantic to load into memory. Let's just consider
		 * that an error.
		 */
		return report(options, &blob->object,
			      FSCK_MSG_GITMODULES_LARGE,
			      ".gitmodules too large to parse");
	}

	data.obj = &blob->object;
	data.options = options;
	data.ret = 0;
	config_opts.error_action = CONFIG_ERROR_SILENT;
	if (git_config_from_mem(fsck_gitmodules_fn, CONFIG_ORIGIN_BLOB,
				".gitmodules", buf, size, &data, &config_opts))
		data.ret |= report(options, &blob->object,
				   FSCK_MSG_GITMODULES_PARSE,
				   "could not parse gitmodules blob");

	return data.ret;
}