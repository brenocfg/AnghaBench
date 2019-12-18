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
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_storage {TYPE_1__ sin_addr; scalar_t__ sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr_in {TYPE_1__ sin_addr; scalar_t__ sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct event_base {int dummy; } ;
struct evdns_server_port {int dummy; } ;
struct evdns_base {int dummy; } ;
typedef  int /*<<< orphan*/  ss ;
typedef  int /*<<< orphan*/  sin ;
typedef  scalar_t__ evutil_socket_t ;
typedef  int ev_socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 scalar_t__ bind (scalar_t__,struct sockaddr*,int) ; 
 struct evdns_server_port* evdns_add_server_port_with_base (struct event_base*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct event_base*) ; 
 int /*<<< orphan*/  evdns_base_free (struct evdns_base*,int) ; 
 int /*<<< orphan*/  evdns_base_nameserver_sockaddr_add (struct evdns_base*,struct sockaddr*,int,int /*<<< orphan*/ ) ; 
 struct evdns_base* evdns_base_new (struct event_base*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evdns_close_server_port (struct evdns_server_port*) ; 
 int /*<<< orphan*/  event_base_dispatch (struct event_base*) ; 
 int /*<<< orphan*/  event_base_free (struct event_base*) ; 
 struct event_base* event_base_new () ; 
 int /*<<< orphan*/  evutil_closesocket (scalar_t__) ; 
 int /*<<< orphan*/  evutil_make_socket_nonblocking (scalar_t__) ; 
 int /*<<< orphan*/  gaic_launch (struct event_base*,struct evdns_base*) ; 
 int /*<<< orphan*/  gaic_server_cb ; 
 scalar_t__ getsockname (scalar_t__,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_storage*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tt_abort_perror (char*) ; 

__attribute__((used)) static void
test_getaddrinfo_async_cancel_stress(void *ptr)
{
	struct event_base *base;
	struct evdns_base *dns_base = NULL;
	struct evdns_server_port *server = NULL;
	evutil_socket_t fd = -1;
	struct sockaddr_in sin;
	struct sockaddr_storage ss;
	ev_socklen_t slen;
	int i;

	base = event_base_new();
	dns_base = evdns_base_new(base, 0);

	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = 0;
	sin.sin_addr.s_addr = htonl(0x7f000001);
	if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		tt_abort_perror("socket");
	}
	evutil_make_socket_nonblocking(fd);
	if (bind(fd, (struct sockaddr*)&sin, sizeof(sin))<0) {
		tt_abort_perror("bind");
	}
	server = evdns_add_server_port_with_base(base, fd, 0, gaic_server_cb,
	    base);

	memset(&ss, 0, sizeof(ss));
	slen = sizeof(ss);
	if (getsockname(fd, (struct sockaddr*)&ss, &slen)<0) {
		tt_abort_perror("getsockname");
	}
	evdns_base_nameserver_sockaddr_add(dns_base,
	    (struct sockaddr*)&ss, slen, 0);

	for (i = 0; i < 1000; ++i) {
		gaic_launch(base, dns_base);
	}

	event_base_dispatch(base);

end:
	if (dns_base)
		evdns_base_free(dns_base, 1);
	if (server)
		evdns_close_server_port(server);
	if (base)
		event_base_free(base);
	if (fd >= 0)
		evutil_closesocket(fd);
}