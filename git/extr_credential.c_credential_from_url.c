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
struct credential {char* path; void* host; int /*<<< orphan*/  protocol; void* password; void* username; } ;

/* Variables and functions */
 int /*<<< orphan*/  credential_clear (struct credential*) ; 
 char* strchr (char const*,char) ; 
 char* strchrnul (char const*,char) ; 
 int strlen (char*) ; 
 char* strstr (char const*,char*) ; 
 char* url_decode (char const*) ; 
 void* url_decode_mem (char const*,int) ; 
 int /*<<< orphan*/  xmemdupz (char const*,int) ; 

void credential_from_url(struct credential *c, const char *url)
{
	const char *at, *colon, *cp, *slash, *host, *proto_end;

	credential_clear(c);

	/*
	 * Match one of:
	 *   (1) proto://<host>/...
	 *   (2) proto://<user>@<host>/...
	 *   (3) proto://<user>:<pass>@<host>/...
	 */
	proto_end = strstr(url, "://");
	if (!proto_end)
		return;
	cp = proto_end + 3;
	at = strchr(cp, '@');
	colon = strchr(cp, ':');
	slash = strchrnul(cp, '/');

	if (!at || slash <= at) {
		/* Case (1) */
		host = cp;
	}
	else if (!colon || at <= colon) {
		/* Case (2) */
		c->username = url_decode_mem(cp, at - cp);
		host = at + 1;
	} else {
		/* Case (3) */
		c->username = url_decode_mem(cp, colon - cp);
		c->password = url_decode_mem(colon + 1, at - (colon + 1));
		host = at + 1;
	}

	if (proto_end - url > 0)
		c->protocol = xmemdupz(url, proto_end - url);
	if (slash - host > 0)
		c->host = url_decode_mem(host, slash - host);
	/* Trim leading and trailing slashes from path */
	while (*slash == '/')
		slash++;
	if (*slash) {
		char *p;
		c->path = url_decode(slash);
		p = c->path + strlen(c->path) - 1;
		while (p > c->path && *p == '/')
			*p-- = '\0';
	}
}