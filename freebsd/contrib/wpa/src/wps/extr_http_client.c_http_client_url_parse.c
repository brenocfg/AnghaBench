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
struct sockaddr_in {void* sin_port; int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int atoi (char*) ; 
 void* htons (int) ; 
 scalar_t__ inet_aton (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 int /*<<< orphan*/  os_memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 char* os_strchr (char*,char) ; 
 char* os_strdup (char const*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char const*,char*,char*) ; 

char * http_client_url_parse(const char *url, struct sockaddr_in *dst,
			     char **ret_path)
{
	char *u, *addr, *port, *path;

	u = os_strdup(url);
	if (u == NULL)
		return NULL;

	os_memset(dst, 0, sizeof(*dst));
	dst->sin_family = AF_INET;
	addr = u + 7;
	path = os_strchr(addr, '/');
	port = os_strchr(addr, ':');
	if (path == NULL) {
		path = "/";
	} else {
		*path = '\0'; /* temporary nul termination for address */
		if (port > path)
			port = NULL;
	}
	if (port)
		*port++ = '\0';

	if (inet_aton(addr, &dst->sin_addr) == 0) {
		/* TODO: name lookup */
		wpa_printf(MSG_DEBUG, "HTTP: Unsupported address in URL '%s' "
			   "(addr='%s' port='%s')",
			   url, addr, port);
		os_free(u);
		return NULL;
	}

	if (port)
		dst->sin_port = htons(atoi(port));
	else
		dst->sin_port = htons(80);

	if (*path == '\0') {
		/* remove temporary nul termination for address */
		*path = '/';
	}

	*ret_path = path;

	return u;
}