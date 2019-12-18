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
struct sockaddr_in {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct event_base {int dummy; } ;
struct evdns_server_port {int dummy; } ;
typedef  int /*<<< orphan*/  my_addr ;
typedef  scalar_t__ evutil_socket_t ;
typedef  int /*<<< orphan*/  evdns_request_callback_fn_type ;
typedef  int /*<<< orphan*/  ev_uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 scalar_t__ bind (scalar_t__,struct sockaddr*,int) ; 
 struct evdns_server_port* evdns_add_server_port_with_base (struct event_base*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  evutil_closesocket (scalar_t__) ; 
 int /*<<< orphan*/  evutil_make_socket_nonblocking (scalar_t__) ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regress_get_socket_port (scalar_t__) ; 
 scalar_t__ socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tt_abort_perror (char*) ; 

struct evdns_server_port *
regress_get_dnsserver(struct event_base *base,
    ev_uint16_t *portnum,
    evutil_socket_t *psock,
    evdns_request_callback_fn_type cb,
    void *arg)
{
	struct evdns_server_port *port = NULL;
	evutil_socket_t sock;
	struct sockaddr_in my_addr;

	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0) {
		tt_abort_perror("socket");
	}

	evutil_make_socket_nonblocking(sock);

	memset(&my_addr, 0, sizeof(my_addr));
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(*portnum);
	my_addr.sin_addr.s_addr = htonl(0x7f000001UL);
	if (bind(sock, (struct sockaddr*)&my_addr, sizeof(my_addr)) < 0) {
		evutil_closesocket(sock);
		tt_abort_perror("bind");
	}
	port = evdns_add_server_port_with_base(base, sock, 0, cb, arg);
	if (!*portnum)
		*portnum = regress_get_socket_port(sock);
	if (psock)
		*psock = sock;

	return port;
end:
	return NULL;
}