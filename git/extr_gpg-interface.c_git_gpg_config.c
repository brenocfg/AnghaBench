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
struct gpg_format {int /*<<< orphan*/  program; } ;

/* Variables and functions */
 int config_error_nonbool (char const*) ; 
 int error (char*,char const*,char const*) ; 
 struct gpg_format* get_format_by_name (char const*) ; 
 int git_config_string (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  set_signing_key (char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 struct gpg_format* use_format ; 

int git_gpg_config(const char *var, const char *value, void *cb)
{
	struct gpg_format *fmt = NULL;
	char *fmtname = NULL;

	if (!strcmp(var, "user.signingkey")) {
		if (!value)
			return config_error_nonbool(var);
		set_signing_key(value);
		return 0;
	}

	if (!strcmp(var, "gpg.format")) {
		if (!value)
			return config_error_nonbool(var);
		fmt = get_format_by_name(value);
		if (!fmt)
			return error("unsupported value for %s: %s",
				     var, value);
		use_format = fmt;
		return 0;
	}

	if (!strcmp(var, "gpg.program") || !strcmp(var, "gpg.openpgp.program"))
		fmtname = "openpgp";

	if (!strcmp(var, "gpg.x509.program"))
		fmtname = "x509";

	if (fmtname) {
		fmt = get_format_by_name(fmtname);
		return git_config_string(&fmt->program, var, value);
	}

	return 0;
}