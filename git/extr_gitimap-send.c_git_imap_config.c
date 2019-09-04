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
struct TYPE_2__ {int use_ssl; int /*<<< orphan*/  auth_method; int /*<<< orphan*/  tunnel; int /*<<< orphan*/  port; int /*<<< orphan*/  pass; int /*<<< orphan*/  user; int /*<<< orphan*/  host; int /*<<< orphan*/  folder; int /*<<< orphan*/  use_html; int /*<<< orphan*/  ssl_verify; } ;

/* Variables and functions */
 int /*<<< orphan*/  git_config_get_bool (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_int (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_string (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_value (char*,char const**) ; 
 int /*<<< orphan*/  git_die_config (char*,char*) ; 
 TYPE_1__ server ; 
 scalar_t__ starts_with (char const*,char*) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

__attribute__((used)) static void git_imap_config(void)
{
	const char *val = NULL;

	git_config_get_bool("imap.sslverify", &server.ssl_verify);
	git_config_get_bool("imap.preformattedhtml", &server.use_html);
	git_config_get_string("imap.folder", &server.folder);

	if (!git_config_get_value("imap.host", &val)) {
		if (!val) {
			git_die_config("imap.host", "Missing value for 'imap.host'");
		} else {
			if (starts_with(val, "imap:"))
				val += 5;
			else if (starts_with(val, "imaps:")) {
				val += 6;
				server.use_ssl = 1;
			}
			if (starts_with(val, "//"))
				val += 2;
			server.host = xstrdup(val);
		}
	}

	git_config_get_string("imap.user", &server.user);
	git_config_get_string("imap.pass", &server.pass);
	git_config_get_int("imap.port", &server.port);
	git_config_get_string("imap.tunnel", &server.tunnel);
	git_config_get_string("imap.authmethod", &server.auth_method);
}