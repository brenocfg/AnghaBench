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
typedef  int /*<<< orphan*/  u8 ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
struct evdns_server_port {int /*<<< orphan*/  socket; } ;
typedef  int /*<<< orphan*/  packet ;
typedef  int ev_socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_LOCKED (struct evdns_server_port*) ; 
 int /*<<< orphan*/  EVDNS_LOG_WARN ; 
 scalar_t__ EVUTIL_ERR_RW_RETRIABLE (int) ; 
 int /*<<< orphan*/  evutil_socket_error_to_string (int) ; 
 int evutil_socket_geterror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int recvfrom (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  request_parse (int /*<<< orphan*/ *,int,struct evdns_server_port*,struct sockaddr*,int) ; 

__attribute__((used)) static void
server_port_read(struct evdns_server_port *s) {
	u8 packet[1500];
	struct sockaddr_storage addr;
	ev_socklen_t addrlen;
	int r;
	ASSERT_LOCKED(s);

	for (;;) {
		addrlen = sizeof(struct sockaddr_storage);
		r = recvfrom(s->socket, (void*)packet, sizeof(packet), 0,
					 (struct sockaddr*) &addr, &addrlen);
		if (r < 0) {
			int err = evutil_socket_geterror(s->socket);
			if (EVUTIL_ERR_RW_RETRIABLE(err))
				return;
			log(EVDNS_LOG_WARN,
			    "Error %s (%d) while reading request.",
			    evutil_socket_error_to_string(err), err);
			return;
		}
		request_parse(packet, r, s, (struct sockaddr*) &addr, addrlen);
	}
}