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
struct nameserver {int /*<<< orphan*/  base; scalar_t__ timedout; int /*<<< orphan*/  address; int /*<<< orphan*/  socket; } ;
typedef  int /*<<< orphan*/  ss ;
typedef  int /*<<< orphan*/  packet ;
typedef  int ev_socklen_t ;
typedef  int /*<<< orphan*/  addrbuf ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_LOCKED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVDNS_LOG_WARN ; 
 scalar_t__ EVUTIL_ERR_RW_RETRIABLE (int) ; 
 int /*<<< orphan*/  evutil_format_sockaddr_port_ (struct sockaddr*,char*,int) ; 
 scalar_t__ evutil_sockaddr_cmp (struct sockaddr*,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evutil_socket_error_to_string (int) ; 
 int evutil_socket_geterror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nameserver_failed (struct nameserver*,int /*<<< orphan*/ ) ; 
 int recvfrom (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  reply_parse (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int const) ; 

__attribute__((used)) static void
nameserver_read(struct nameserver *ns) {
	struct sockaddr_storage ss;
	ev_socklen_t addrlen = sizeof(ss);
	u8 packet[1500];
	char addrbuf[128];
	ASSERT_LOCKED(ns->base);

	for (;;) {
		const int r = recvfrom(ns->socket, (void*)packet,
		    sizeof(packet), 0,
		    (struct sockaddr*)&ss, &addrlen);
		if (r < 0) {
			int err = evutil_socket_geterror(ns->socket);
			if (EVUTIL_ERR_RW_RETRIABLE(err))
				return;
			nameserver_failed(ns,
			    evutil_socket_error_to_string(err));
			return;
		}
		if (evutil_sockaddr_cmp((struct sockaddr*)&ss,
			(struct sockaddr*)&ns->address, 0)) {
			log(EVDNS_LOG_WARN, "Address mismatch on received "
			    "DNS packet.  Apparent source was %s",
			    evutil_format_sockaddr_port_(
				    (struct sockaddr *)&ss,
				    addrbuf, sizeof(addrbuf)));
			return;
		}

		ns->timedout = 0;
		reply_parse(ns->base, packet, r);
	}
}