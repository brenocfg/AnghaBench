#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* host; int use_ssl; char* path; int /*<<< orphan*/  pass; int /*<<< orphan*/  user; int /*<<< orphan*/  port; } ;
typedef  TYPE_1__ gitno_connection_data ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_NET ; 
 int /*<<< orphan*/  assert (int) ; 
 char* default_port_http ; 
 char* default_port_https ; 
 int /*<<< orphan*/  git__free (char*) ; 
 int /*<<< orphan*/  git__prefixcmp (char const*,char const*) ; 
 char* git__strdup (char const*) ; 
 char* git__strndup (char const*,size_t) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 char* gitno__default_port (TYPE_1__*) ; 
 int /*<<< orphan*/  gitno_connection_data_free_ptrs (TYPE_1__*) ; 
 int gitno_extract_url_parts (char**,int /*<<< orphan*/ *,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  memcmp (char const*,char const*,size_t) ; 
 char const* prefix_http ; 
 char const* prefix_https ; 
 char* strchr (char const*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 size_t strlen (char const*) ; 

int gitno_connection_data_from_url(
		gitno_connection_data *data,
		const char *url,
		const char *service_suffix)
{
	int error = -1;
	const char *default_port = NULL, *path_search_start = NULL;
	char *original_host = NULL;

	/* service_suffix is optional */
	assert(data && url);

	/* Save these for comparison later */
	original_host = data->host;
	data->host = NULL;
	gitno_connection_data_free_ptrs(data);

	if (!git__prefixcmp(url, prefix_http)) {
		path_search_start = url + strlen(prefix_http);
		default_port = default_port_http;

		if (data->use_ssl) {
			git_error_set(GIT_ERROR_NET, "redirect from HTTPS to HTTP is not allowed");
			goto cleanup;
		}
	} else if (!git__prefixcmp(url, prefix_https)) {
		path_search_start = url + strlen(prefix_https);
		default_port = default_port_https;
		data->use_ssl = true;
	} else if (url[0] == '/')
		default_port = gitno__default_port(data);

	if (!default_port) {
		git_error_set(GIT_ERROR_NET, "unrecognized URL prefix");
		goto cleanup;
	}

	error = gitno_extract_url_parts(
		&data->host, &data->port, &data->path, &data->user, &data->pass,
		url, default_port);

	if (url[0] == '/') {
		/* Relative redirect; reuse original host name and port */
		path_search_start = url;
		git__free(data->host);
		data->host = original_host;
		original_host = NULL;
	}

	if (!error) {
		const char *path = strchr(path_search_start, '/');
		size_t pathlen = strlen(path);
		size_t suffixlen = service_suffix ? strlen(service_suffix) : 0;

		if (suffixlen &&
		    !memcmp(path + pathlen - suffixlen, service_suffix, suffixlen)) {
			git__free(data->path);
			data->path = git__strndup(path, pathlen - suffixlen);
		} else {
			git__free(data->path);
			data->path = git__strdup(path);
		}

		/* Check for errors in the resulting data */
		if (original_host && url[0] != '/' && strcmp(original_host, data->host)) {
			git_error_set(GIT_ERROR_NET, "cross host redirect not allowed");
			error = -1;
		}
	}

cleanup:
	if (original_host) git__free(original_host);
	return error;
}