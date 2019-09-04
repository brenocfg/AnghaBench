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
struct http_parser_url {int field_set; TYPE_1__* field_data; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  git_buf ;
struct TYPE_2__ {int off; size_t len; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int GIT_EINVALIDSPEC ; 
 int /*<<< orphan*/  GIT_ERROR_NET ; 
 int UF_HOST ; 
 int UF_PATH ; 
 int UF_PORT ; 
 int UF_USERINFO ; 
 int /*<<< orphan*/  git_buf_decode_percent (int /*<<< orphan*/ *,char const*,size_t) ; 
 char* git_buf_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 scalar_t__ git_buf_oom (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_put (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  git_buf_puts (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ http_parser_parse_url (char const*,int /*<<< orphan*/ ,int,struct http_parser_url*) ; 
 char* memchr (char const*,char,size_t) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int gitno_extract_url_parts(
	char **host_out,
	char **port_out,
	char **path_out,
	char **username_out,
	char **password_out,
	const char *url,
	const char *default_port)
{
	struct http_parser_url u = {0};
	bool has_host, has_port, has_path, has_userinfo;
	git_buf host = GIT_BUF_INIT,
		port = GIT_BUF_INIT,
		path = GIT_BUF_INIT,
		username = GIT_BUF_INIT,
		password = GIT_BUF_INIT;
	int error = 0;

	if (http_parser_parse_url(url, strlen(url), false, &u)) {
		git_error_set(GIT_ERROR_NET, "malformed URL '%s'", url);
		error = GIT_EINVALIDSPEC;
		goto done;
	}

	has_host = !!(u.field_set & (1 << UF_HOST));
	has_port = !!(u.field_set & (1 << UF_PORT));
	has_path = !!(u.field_set & (1 << UF_PATH));
	has_userinfo = !!(u.field_set & (1 << UF_USERINFO));

	if (has_host) {
		const char *url_host = url + u.field_data[UF_HOST].off;
		size_t url_host_len = u.field_data[UF_HOST].len;
		git_buf_decode_percent(&host, url_host, url_host_len);
	}

	if (has_port) {
		const char *url_port = url + u.field_data[UF_PORT].off;
		size_t url_port_len = u.field_data[UF_PORT].len;
		git_buf_put(&port, url_port, url_port_len);
	} else {
		git_buf_puts(&port, default_port);
	}

	if (has_path && path_out) {
		const char *url_path = url + u.field_data[UF_PATH].off;
		size_t url_path_len = u.field_data[UF_PATH].len;
		git_buf_decode_percent(&path, url_path, url_path_len);
	} else if (path_out) {
		git_error_set(GIT_ERROR_NET, "invalid url, missing path");
		error = GIT_EINVALIDSPEC;
		goto done;
	}

	if (has_userinfo) {
		const char *url_userinfo = url + u.field_data[UF_USERINFO].off;
		size_t url_userinfo_len = u.field_data[UF_USERINFO].len;
		const char *colon = memchr(url_userinfo, ':', url_userinfo_len);

		if (colon) {
			const char *url_username = url_userinfo;
			size_t url_username_len = colon - url_userinfo;
			const char *url_password = colon + 1;
			size_t url_password_len = url_userinfo_len - (url_username_len + 1);

			git_buf_decode_percent(&username, url_username, url_username_len);
			git_buf_decode_percent(&password, url_password, url_password_len);
		} else {
			git_buf_decode_percent(&username, url_userinfo, url_userinfo_len);
		}
	}

	if (git_buf_oom(&host) ||
		git_buf_oom(&port) ||
		git_buf_oom(&path) ||
		git_buf_oom(&username) ||
		git_buf_oom(&password))
		return -1;

	*host_out = git_buf_detach(&host);
	*port_out = git_buf_detach(&port);
	if (path_out)
		*path_out = git_buf_detach(&path);
	*username_out = git_buf_detach(&username);
	*password_out = git_buf_detach(&password);

done:
	git_buf_dispose(&host);
	git_buf_dispose(&port);
	git_buf_dispose(&path);
	git_buf_dispose(&username);
	git_buf_dispose(&password);
	return error;
}