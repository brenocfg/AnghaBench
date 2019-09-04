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
struct tracking_name_data {char const* default_remote; char* src_ref; int num_matches; char* default_dst_ref; char* default_dst_oid; char const* dst_ref; struct object_id* dst_oid; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 struct tracking_name_data TRACKING_NAME_DATA_INIT ; 
 int /*<<< orphan*/  check_tracking_name ; 
 int /*<<< orphan*/  for_each_remote (int /*<<< orphan*/ ,struct tracking_name_data*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  git_config_get_string_const (char*,char const**) ; 
 int /*<<< orphan*/  oidcpy (struct object_id*,char*) ; 
 char* xstrfmt (char*,char const*) ; 

const char *unique_tracking_name(const char *name, struct object_id *oid,
				 int *dwim_remotes_matched)
{
	struct tracking_name_data cb_data = TRACKING_NAME_DATA_INIT;
	const char *default_remote = NULL;
	if (!git_config_get_string_const("checkout.defaultremote", &default_remote))
		cb_data.default_remote = default_remote;
	cb_data.src_ref = xstrfmt("refs/heads/%s", name);
	cb_data.dst_oid = oid;
	for_each_remote(check_tracking_name, &cb_data);
	if (dwim_remotes_matched)
		*dwim_remotes_matched = cb_data.num_matches;
	free(cb_data.src_ref);
	free((char *)default_remote);
	if (cb_data.num_matches == 1) {
		free(cb_data.default_dst_ref);
		free(cb_data.default_dst_oid);
		return cb_data.dst_ref;
	}
	free(cb_data.dst_ref);
	if (cb_data.default_dst_ref) {
		oidcpy(oid, cb_data.default_dst_oid);
		free(cb_data.default_dst_oid);
		return cb_data.default_dst_ref;
	}
	return NULL;
}