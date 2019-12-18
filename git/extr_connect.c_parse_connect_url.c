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
typedef  enum protocol { ____Placeholder_protocol } protocol ;

/* Variables and functions */
 int PROTO_FILE ; 
 int PROTO_GIT ; 
 int PROTO_LOCAL ; 
 int PROTO_SSH ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int get_protocol (char*) ; 
 scalar_t__ has_dos_drive_prefix (char*) ; 
 char* host_end (char**,int /*<<< orphan*/ ) ; 
 scalar_t__ is_url (char const*) ; 
 int offset_1st_component (char*) ; 
 char* strchr (char*,int) ; 
 char* strstr (char*,char*) ; 
 char* url_decode (char const*) ; 
 int /*<<< orphan*/  url_is_local_not_ssh (char*) ; 
 char* xstrdup (char const*) ; 

__attribute__((used)) static enum protocol parse_connect_url(const char *url_orig, char **ret_host,
				       char **ret_path)
{
	char *url;
	char *host, *path;
	char *end;
	int separator = '/';
	enum protocol protocol = PROTO_LOCAL;

	if (is_url(url_orig))
		url = url_decode(url_orig);
	else
		url = xstrdup(url_orig);

	host = strstr(url, "://");
	if (host) {
		*host = '\0';
		protocol = get_protocol(url);
		host += 3;
	} else {
		host = url;
		if (!url_is_local_not_ssh(url)) {
			protocol = PROTO_SSH;
			separator = ':';
		}
	}

	/*
	 * Don't do destructive transforms as protocol code does
	 * '[]' unwrapping in get_host_and_port()
	 */
	end = host_end(&host, 0);

	if (protocol == PROTO_LOCAL)
		path = end;
	else if (protocol == PROTO_FILE && *host != '/' &&
		 !has_dos_drive_prefix(host) &&
		 offset_1st_component(host - 2) > 1)
		path = host - 2; /* include the leading "//" */
	else if (protocol == PROTO_FILE && has_dos_drive_prefix(end))
		path = end; /* "file://$(pwd)" may be "file://C:/projects/repo" */
	else
		path = strchr(end, separator);

	if (!path || !*path)
		die(_("no path specified; see 'git help pull' for valid url syntax"));

	/*
	 * null-terminate hostname and point path to ~ for URL's like this:
	 *    ssh://host.xz/~user/repo
	 */

	end = path; /* Need to \0 terminate host here */
	if (separator == ':')
		path++; /* path starts after ':' */
	if (protocol == PROTO_GIT || protocol == PROTO_SSH) {
		if (path[1] == '~')
			path++;
	}

	path = xstrdup(path);
	*end = '\0';

	*ret_host = xstrdup(host);
	*ret_path = path;
	free(url);
	return protocol;
}