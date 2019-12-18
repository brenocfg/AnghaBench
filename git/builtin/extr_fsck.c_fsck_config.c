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
struct strbuf {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  fsck_obj_options ; 
 int /*<<< orphan*/  fsck_set_msg_type (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  fsck_set_msg_types (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ git_config_pathname (char const**,char const*,char const*) ; 
 int git_default_config (char const*,char const*,void*) ; 
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int fsck_config(const char *var, const char *value, void *cb)
{
	if (strcmp(var, "fsck.skiplist") == 0) {
		const char *path;
		struct strbuf sb = STRBUF_INIT;

		if (git_config_pathname(&path, var, value))
			return 1;
		strbuf_addf(&sb, "skiplist=%s", path);
		free((char *)path);
		fsck_set_msg_types(&fsck_obj_options, sb.buf);
		strbuf_release(&sb);
		return 0;
	}

	if (skip_prefix(var, "fsck.", &var)) {
		fsck_set_msg_type(&fsck_obj_options, var, value);
		return 0;
	}

	return git_default_config(var, value, cb);
}