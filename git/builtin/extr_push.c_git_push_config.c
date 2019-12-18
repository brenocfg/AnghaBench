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
 int RECURSE_SUBMODULES_OFF ; 
 int RECURSE_SUBMODULES_ON_DEMAND ; 
 int /*<<< orphan*/  SEND_PACK_PUSH_CERT_ALWAYS ; 
 int /*<<< orphan*/  SEND_PACK_PUSH_CERT_IF_ASKED ; 
 int /*<<< orphan*/  SEND_PACK_PUSH_CERT_NEVER ; 
 int TRANSPORT_PUSH_FOLLOW_TAGS ; 
 int color_parse (char const*,int /*<<< orphan*/ ) ; 
 int config_error_nonbool (char const*) ; 
 int error (char*,char const*) ; 
 scalar_t__ git_config_bool (char const*,char const*) ; 
 int /*<<< orphan*/  git_config_colorbool (char const*,char const*) ; 
 int /*<<< orphan*/  git_config_get_value (char*,char const**) ; 
 int git_default_config (char const*,char const*,int /*<<< orphan*/ *) ; 
 int git_gpg_config (char const*,char const*,int /*<<< orphan*/ *) ; 
 int git_parse_maybe_bool (char const*) ; 
 int parse_push_color_slot (char const*) ; 
 int parse_push_recurse_submodules_arg (char const*,char const*) ; 
 int /*<<< orphan*/ * push_colors ; 
 int /*<<< orphan*/  push_options_config ; 
 int /*<<< orphan*/  push_use_color ; 
 int recurse_submodules ; 
 int /*<<< orphan*/  set_push_cert_flags (int*,int /*<<< orphan*/ ) ; 
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  string_list_append (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  string_list_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int git_push_config(const char *k, const char *v, void *cb)
{
	const char *slot_name;
	int *flags = cb;
	int status;

	status = git_gpg_config(k, v, NULL);
	if (status)
		return status;

	if (!strcmp(k, "push.followtags")) {
		if (git_config_bool(k, v))
			*flags |= TRANSPORT_PUSH_FOLLOW_TAGS;
		else
			*flags &= ~TRANSPORT_PUSH_FOLLOW_TAGS;
		return 0;
	} else if (!strcmp(k, "push.gpgsign")) {
		const char *value;
		if (!git_config_get_value("push.gpgsign", &value)) {
			switch (git_parse_maybe_bool(value)) {
			case 0:
				set_push_cert_flags(flags, SEND_PACK_PUSH_CERT_NEVER);
				break;
			case 1:
				set_push_cert_flags(flags, SEND_PACK_PUSH_CERT_ALWAYS);
				break;
			default:
				if (value && !strcasecmp(value, "if-asked"))
					set_push_cert_flags(flags, SEND_PACK_PUSH_CERT_IF_ASKED);
				else
					return error("Invalid value for '%s'", k);
			}
		}
	} else if (!strcmp(k, "push.recursesubmodules")) {
		const char *value;
		if (!git_config_get_value("push.recursesubmodules", &value))
			recurse_submodules = parse_push_recurse_submodules_arg(k, value);
	} else if (!strcmp(k, "submodule.recurse")) {
		int val = git_config_bool(k, v) ?
			RECURSE_SUBMODULES_ON_DEMAND : RECURSE_SUBMODULES_OFF;
		recurse_submodules = val;
	} else if (!strcmp(k, "push.pushoption")) {
		if (!v)
			return config_error_nonbool(k);
		else
			if (!*v)
				string_list_clear(&push_options_config, 0);
			else
				string_list_append(&push_options_config, v);
		return 0;
	} else if (!strcmp(k, "color.push")) {
		push_use_color = git_config_colorbool(k, v);
		return 0;
	} else if (skip_prefix(k, "color.push.", &slot_name)) {
		int slot = parse_push_color_slot(slot_name);
		if (slot < 0)
			return 0;
		if (!v)
			return config_error_nonbool(k);
		return color_parse(v, push_colors[slot]);
	}

	return git_default_config(k, v, NULL);
}