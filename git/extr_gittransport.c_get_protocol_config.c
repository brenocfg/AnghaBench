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
typedef  enum protocol_allow_config { ____Placeholder_protocol_allow_config } protocol_allow_config ;

/* Variables and functions */
 int PROTOCOL_ALLOW_ALWAYS ; 
 int PROTOCOL_ALLOW_NEVER ; 
 int PROTOCOL_ALLOW_USER_ONLY ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  git_config_get_string (char*,char**) ; 
 int parse_protocol_config (char*,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 char* xstrfmt (char*,char const*) ; 

__attribute__((used)) static enum protocol_allow_config get_protocol_config(const char *type)
{
	char *key = xstrfmt("protocol.%s.allow", type);
	char *value;

	/* first check the per-protocol config */
	if (!git_config_get_string(key, &value)) {
		enum protocol_allow_config ret =
			parse_protocol_config(key, value);
		free(key);
		free(value);
		return ret;
	}
	free(key);

	/* if defined, fallback to user-defined default for unknown protocols */
	if (!git_config_get_string("protocol.allow", &value)) {
		enum protocol_allow_config ret =
			parse_protocol_config("protocol.allow", value);
		free(value);
		return ret;
	}

	/* fallback to built-in defaults */
	/* known safe */
	if (!strcmp(type, "http") ||
	    !strcmp(type, "https") ||
	    !strcmp(type, "git") ||
	    !strcmp(type, "ssh") ||
	    !strcmp(type, "file"))
		return PROTOCOL_ALLOW_ALWAYS;

	/* known scary; err on the side of caution */
	if (!strcmp(type, "ext"))
		return PROTOCOL_ALLOW_NEVER;

	/* unknown; by default let them be used only directly by the user */
	return PROTOCOL_ALLOW_USER_ONLY;
}