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
struct sockaddr {int dummy; } ;
struct evhttp_connection {int dummy; } ;
typedef  int /*<<< orphan*/  local ;
typedef  int /*<<< orphan*/  addrbuf ;

/* Variables and functions */
 struct sockaddr* evhttp_connection_get_addr (struct evhttp_connection*) ; 
 int /*<<< orphan*/  evutil_format_sockaddr_port_ (struct sockaddr*,char*,int) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int test_ok ; 
 int /*<<< orphan*/  tt_assert (int) ; 

__attribute__((used)) static void
http_request_get_addr_on_close(struct evhttp_connection *evcon, void *arg)
{
	const struct sockaddr *storage;
	char addrbuf[128];
	char local[] = "127.0.0.1:";

	test_ok = 0;
	tt_assert(evcon);

	storage = evhttp_connection_get_addr(evcon);
	tt_assert(storage);

	evutil_format_sockaddr_port_((struct sockaddr *)storage, addrbuf, sizeof(addrbuf));
	tt_assert(!strncmp(addrbuf, local, sizeof(local) - 1));

	test_ok = 1;
	return;

end:
	test_ok = 0;
}