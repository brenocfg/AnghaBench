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
 int /*<<< orphan*/  ALLOW_ANY_SHA1 ; 
 int /*<<< orphan*/  ALLOW_REACHABLE_SHA1 ; 
 int /*<<< orphan*/  ALLOW_TIP_SHA1 ; 
 scalar_t__ CONFIG_SCOPE_REPO ; 
 void* allow_filter ; 
 void* allow_ref_in_want ; 
 void* allow_sideband_all ; 
 int /*<<< orphan*/  allow_unadvertised_object_request ; 
 scalar_t__ current_config_scope () ; 
 void* git_config_bool (char const*,char const*) ; 
 int git_config_int (char const*,char const*) ; 
 int git_config_string (int /*<<< orphan*/ *,char const*,char const*) ; 
 int keepalive ; 
 int /*<<< orphan*/  pack_objects_hook ; 
 int parse_hide_refs_config (char const*,char const*,char*) ; 
 void* precomposed_unicode ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 

__attribute__((used)) static int upload_pack_config(const char *var, const char *value, void *unused)
{
	if (!strcmp("uploadpack.allowtipsha1inwant", var)) {
		if (git_config_bool(var, value))
			allow_unadvertised_object_request |= ALLOW_TIP_SHA1;
		else
			allow_unadvertised_object_request &= ~ALLOW_TIP_SHA1;
	} else if (!strcmp("uploadpack.allowreachablesha1inwant", var)) {
		if (git_config_bool(var, value))
			allow_unadvertised_object_request |= ALLOW_REACHABLE_SHA1;
		else
			allow_unadvertised_object_request &= ~ALLOW_REACHABLE_SHA1;
	} else if (!strcmp("uploadpack.allowanysha1inwant", var)) {
		if (git_config_bool(var, value))
			allow_unadvertised_object_request |= ALLOW_ANY_SHA1;
		else
			allow_unadvertised_object_request &= ~ALLOW_ANY_SHA1;
	} else if (!strcmp("uploadpack.keepalive", var)) {
		keepalive = git_config_int(var, value);
		if (!keepalive)
			keepalive = -1;
	} else if (!strcmp("uploadpack.allowfilter", var)) {
		allow_filter = git_config_bool(var, value);
	} else if (!strcmp("uploadpack.allowrefinwant", var)) {
		allow_ref_in_want = git_config_bool(var, value);
	} else if (!strcmp("uploadpack.allowsidebandall", var)) {
		allow_sideband_all = git_config_bool(var, value);
	} else if (!strcmp("core.precomposeunicode", var)) {
		precomposed_unicode = git_config_bool(var, value);
	}

	if (current_config_scope() != CONFIG_SCOPE_REPO) {
		if (!strcmp("uploadpack.packobjectshook", var))
			return git_config_string(&pack_objects_hook, var, value);
	}

	return parse_hide_refs_config(var, value, "uploadpack");
}