#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct http_parser_url {int field_set; TYPE_1__* field_data; int /*<<< orphan*/  member_0; } ;
struct TYPE_13__ {void* password; void* username; void* query; void* path; void* port; void* host; void* scheme; } ;
typedef  TYPE_2__ git_net_url ;
struct TYPE_14__ {int /*<<< orphan*/  ptr; int /*<<< orphan*/  size; } ;
typedef  TYPE_3__ git_buf ;
struct TYPE_12__ {int off; size_t len; } ;

/* Variables and functions */
 TYPE_3__ GIT_BUF_INIT ; 
 int GIT_EINVALIDSPEC ; 
 int /*<<< orphan*/  GIT_ERROR_NET ; 
 int UF_HOST ; 
 int UF_PATH ; 
 int UF_PORT ; 
 int UF_QUERY ; 
 int UF_SCHEMA ; 
 int UF_USERINFO ; 
 char* default_port_for_scheme (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git__strntolower (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_decode_percent (TYPE_3__*,char const*,size_t) ; 
 void* git_buf_detach (TYPE_3__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_3__*) ; 
 scalar_t__ git_buf_oom (TYPE_3__*) ; 
 int /*<<< orphan*/  git_buf_put (TYPE_3__*,char const*,size_t) ; 
 int /*<<< orphan*/  git_buf_puts (TYPE_3__*,char const*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ http_parser_parse_url (char const*,int /*<<< orphan*/ ,int,struct http_parser_url*) ; 
 char* memchr (char const*,char,size_t) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int git_net_url_parse(git_net_url *url, const char *given)
{
	struct http_parser_url u = {0};
	bool has_scheme, has_host, has_port, has_path, has_query, has_userinfo;
	git_buf scheme = GIT_BUF_INIT,
		host = GIT_BUF_INIT,
		port = GIT_BUF_INIT,
		path = GIT_BUF_INIT,
		username = GIT_BUF_INIT,
		password = GIT_BUF_INIT,
		query = GIT_BUF_INIT;
	int error = GIT_EINVALIDSPEC;

	if (http_parser_parse_url(given, strlen(given), false, &u)) {
		git_error_set(GIT_ERROR_NET, "malformed URL '%s'", given);
		goto done;
	}

	has_scheme = !!(u.field_set & (1 << UF_SCHEMA));
	has_host = !!(u.field_set & (1 << UF_HOST));
	has_port = !!(u.field_set & (1 << UF_PORT));
	has_path = !!(u.field_set & (1 << UF_PATH));
	has_query = !!(u.field_set & (1 << UF_QUERY));
	has_userinfo = !!(u.field_set & (1 << UF_USERINFO));

	if (has_scheme) {
		const char *url_scheme = given + u.field_data[UF_SCHEMA].off;
		size_t url_scheme_len = u.field_data[UF_SCHEMA].len;
		git_buf_put(&scheme, url_scheme, url_scheme_len);
		git__strntolower(scheme.ptr, scheme.size);
	} else {
		git_error_set(GIT_ERROR_NET, "malformed URL '%s'", given);
		goto done;
	}

	if (has_host) {
		const char *url_host = given + u.field_data[UF_HOST].off;
		size_t url_host_len = u.field_data[UF_HOST].len;
		git_buf_decode_percent(&host, url_host, url_host_len);
	}

	if (has_port) {
		const char *url_port = given + u.field_data[UF_PORT].off;
		size_t url_port_len = u.field_data[UF_PORT].len;
		git_buf_put(&port, url_port, url_port_len);
	} else {
		const char *default_port = default_port_for_scheme(scheme.ptr);

		if (default_port == NULL) {
			git_error_set(GIT_ERROR_NET, "unknown scheme for URL '%s'", given);
			goto done;
		}

		git_buf_puts(&port, default_port);
	}

	if (has_path) {
		const char *url_path = given + u.field_data[UF_PATH].off;
		size_t url_path_len = u.field_data[UF_PATH].len;
		git_buf_put(&path, url_path, url_path_len);
	} else {
		git_buf_puts(&path, "/");
	}

	if (has_query) {
		const char *url_query = given + u.field_data[UF_QUERY].off;
		size_t url_query_len = u.field_data[UF_QUERY].len;
		git_buf_decode_percent(&query, url_query, url_query_len);
	}

	if (has_userinfo) {
		const char *url_userinfo = given + u.field_data[UF_USERINFO].off;
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

	if (git_buf_oom(&scheme) ||
	    git_buf_oom(&host) ||
	    git_buf_oom(&port) ||
	    git_buf_oom(&path) ||
	    git_buf_oom(&query) ||
	    git_buf_oom(&username) ||
	    git_buf_oom(&password))
		return -1;

	url->scheme = git_buf_detach(&scheme);
	url->host = git_buf_detach(&host);
	url->port = git_buf_detach(&port);
	url->path = git_buf_detach(&path);
	url->query = git_buf_detach(&query);
	url->username = git_buf_detach(&username);
	url->password = git_buf_detach(&password);

	error = 0;

done:
	git_buf_dispose(&scheme);
	git_buf_dispose(&host);
	git_buf_dispose(&port);
	git_buf_dispose(&path);
	git_buf_dispose(&query);
	git_buf_dispose(&username);
	git_buf_dispose(&password);
	return error;
}