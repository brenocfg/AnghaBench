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
struct evhttp_uri {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  URI_SET_STR_ (char const*) ; 
 int /*<<< orphan*/  bracket_addr_ok (char const*,char const*) ; 
 int /*<<< orphan*/  regname_ok (char const*,char const*) ; 
 int strlen (char const*) ; 

int
evhttp_uri_set_host(struct evhttp_uri *uri, const char *host)
{
	if (host) {
		if (host[0] == '[') {
			if (! bracket_addr_ok(host, host+strlen(host)))
				return -1;
		} else {
			if (! regname_ok(host, host+strlen(host)))
				return -1;
		}
	}

	URI_SET_STR_(host);
	return 0;
}