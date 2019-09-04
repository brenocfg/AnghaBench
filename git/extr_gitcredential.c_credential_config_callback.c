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
struct credential {int /*<<< orphan*/  use_http_path; scalar_t__ username; int /*<<< orphan*/  helpers; } ;

/* Variables and functions */
 struct credential CREDENTIAL_INIT ; 
 int config_error_nonbool (char const*) ; 
 int /*<<< orphan*/  credential_clear (struct credential*) ; 
 int /*<<< orphan*/  credential_from_url (struct credential*,char*) ; 
 int credential_match (struct credential*,struct credential*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  git_config_bool (char const*,char const*) ; 
 int /*<<< orphan*/  skip_prefix (char const*,char*,char const**) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  string_list_append (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  string_list_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* strrchr (char const*,char) ; 
 char* xmemdupz (char const*,int) ; 
 scalar_t__ xstrdup (char const*) ; 

__attribute__((used)) static int credential_config_callback(const char *var, const char *value,
				      void *data)
{
	struct credential *c = data;
	const char *key, *dot;

	if (!skip_prefix(var, "credential.", &key))
		return 0;

	if (!value)
		return config_error_nonbool(var);

	dot = strrchr(key, '.');
	if (dot) {
		struct credential want = CREDENTIAL_INIT;
		char *url = xmemdupz(key, dot - key);
		int matched;

		credential_from_url(&want, url);
		matched = credential_match(&want, c);

		credential_clear(&want);
		free(url);

		if (!matched)
			return 0;
		key = dot + 1;
	}

	if (!strcmp(key, "helper")) {
		if (*value)
			string_list_append(&c->helpers, value);
		else
			string_list_clear(&c->helpers, 0);
	} else if (!strcmp(key, "username")) {
		if (!c->username)
			c->username = xstrdup(value);
	}
	else if (!strcmp(key, "usehttppath"))
		c->use_http_path = git_config_bool(var, value);

	return 0;
}