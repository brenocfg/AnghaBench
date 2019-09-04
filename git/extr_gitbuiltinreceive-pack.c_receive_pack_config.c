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
struct TYPE_3__ {scalar_t__ len; } ;

/* Variables and functions */
 void* advertise_atomic_push ; 
 void* advertise_push_options ; 
 void* auto_gc ; 
 void* auto_update_server_info ; 
 int /*<<< orphan*/  cert_nonce_seed ; 
 void* deny_current_branch ; 
 void* deny_delete_current ; 
 void* deny_deletes ; 
 void* deny_non_fast_forwards ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_1__ fsck_msg_types ; 
 void* git_config_bool (char const*,char const*) ; 
 void* git_config_int (char const*,char const*) ; 
 int /*<<< orphan*/  git_config_int64 (char const*,char const*) ; 
 scalar_t__ git_config_pathname (char const**,char const*,char const*) ; 
 int git_config_string (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  git_config_ulong (char const*,char const*) ; 
 int git_default_config (char const*,char const*,void*) ; 
 scalar_t__ is_valid_msg_type (char const*,char const*) ; 
 void* keepalive_in_sec ; 
 int /*<<< orphan*/  max_input_size ; 
 int /*<<< orphan*/  nonce_stamp_slop_limit ; 
 void* parse_deny_action (char const*,char const*) ; 
 int parse_hide_refs_config (char const*,char const*,char*) ; 
 void* prefer_ofs_delta ; 
 void* receive_fsck_objects ; 
 void* receive_unpack_limit ; 
 void* shallow_update ; 
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 
 int /*<<< orphan*/  strbuf_addf (TYPE_1__*,char*,char,char const*,...) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 void* transfer_fsck_objects ; 
 void* transfer_unpack_limit ; 
 int /*<<< orphan*/  warning (char*,char const*) ; 

__attribute__((used)) static int receive_pack_config(const char *var, const char *value, void *cb)
{
	int status = parse_hide_refs_config(var, value, "receive");

	if (status)
		return status;

	if (strcmp(var, "receive.denydeletes") == 0) {
		deny_deletes = git_config_bool(var, value);
		return 0;
	}

	if (strcmp(var, "receive.denynonfastforwards") == 0) {
		deny_non_fast_forwards = git_config_bool(var, value);
		return 0;
	}

	if (strcmp(var, "receive.unpacklimit") == 0) {
		receive_unpack_limit = git_config_int(var, value);
		return 0;
	}

	if (strcmp(var, "transfer.unpacklimit") == 0) {
		transfer_unpack_limit = git_config_int(var, value);
		return 0;
	}

	if (strcmp(var, "receive.fsck.skiplist") == 0) {
		const char *path;

		if (git_config_pathname(&path, var, value))
			return 1;
		strbuf_addf(&fsck_msg_types, "%cskiplist=%s",
			fsck_msg_types.len ? ',' : '=', path);
		free((char *)path);
		return 0;
	}

	if (skip_prefix(var, "receive.fsck.", &var)) {
		if (is_valid_msg_type(var, value))
			strbuf_addf(&fsck_msg_types, "%c%s=%s",
				fsck_msg_types.len ? ',' : '=', var, value);
		else
			warning("Skipping unknown msg id '%s'", var);
		return 0;
	}

	if (strcmp(var, "receive.fsckobjects") == 0) {
		receive_fsck_objects = git_config_bool(var, value);
		return 0;
	}

	if (strcmp(var, "transfer.fsckobjects") == 0) {
		transfer_fsck_objects = git_config_bool(var, value);
		return 0;
	}

	if (!strcmp(var, "receive.denycurrentbranch")) {
		deny_current_branch = parse_deny_action(var, value);
		return 0;
	}

	if (strcmp(var, "receive.denydeletecurrent") == 0) {
		deny_delete_current = parse_deny_action(var, value);
		return 0;
	}

	if (strcmp(var, "repack.usedeltabaseoffset") == 0) {
		prefer_ofs_delta = git_config_bool(var, value);
		return 0;
	}

	if (strcmp(var, "receive.updateserverinfo") == 0) {
		auto_update_server_info = git_config_bool(var, value);
		return 0;
	}

	if (strcmp(var, "receive.autogc") == 0) {
		auto_gc = git_config_bool(var, value);
		return 0;
	}

	if (strcmp(var, "receive.shallowupdate") == 0) {
		shallow_update = git_config_bool(var, value);
		return 0;
	}

	if (strcmp(var, "receive.certnonceseed") == 0)
		return git_config_string(&cert_nonce_seed, var, value);

	if (strcmp(var, "receive.certnonceslop") == 0) {
		nonce_stamp_slop_limit = git_config_ulong(var, value);
		return 0;
	}

	if (strcmp(var, "receive.advertiseatomic") == 0) {
		advertise_atomic_push = git_config_bool(var, value);
		return 0;
	}

	if (strcmp(var, "receive.advertisepushoptions") == 0) {
		advertise_push_options = git_config_bool(var, value);
		return 0;
	}

	if (strcmp(var, "receive.keepalive") == 0) {
		keepalive_in_sec = git_config_int(var, value);
		return 0;
	}

	if (strcmp(var, "receive.maxinputsize") == 0) {
		max_input_size = git_config_int64(var, value);
		return 0;
	}

	return git_default_config(var, value, cb);
}