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
struct addrinfo {int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; struct addrinfo* ai_next; int /*<<< orphan*/  ai_flags; } ;
typedef  int /*<<< orphan*/  hints ;
typedef  int /*<<< orphan*/  heim_sipc ;

/* Variables and functions */
 int /*<<< orphan*/  AI_PASSIVE ; 
 int /*<<< orphan*/  HEIM_SIPC_TYPE_HTTP ; 
 int /*<<< orphan*/  PF_UNSPEC ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 scalar_t__ bind (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errx (int,char*,int) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int gai_strerror (int) ; 
 int getaddrinfo (int /*<<< orphan*/ *,char*,struct addrinfo*,struct addrinfo**) ; 
 int heim_sipc_stream_listener (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listen (int,int) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_set_ipv6only (int,int) ; 
 int /*<<< orphan*/  socket_set_reuseaddr (int,int) ; 
 int /*<<< orphan*/  test_service ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static void
setup_sockets(void)
{
    struct addrinfo hints, *res, *res0;
    int ret, s;
    heim_sipc u;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = PF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    ret = getaddrinfo(NULL, "8080", &hints, &res0);
    if (ret)
	errx(1, "%s", gai_strerror(ret));

    for (res = res0; res ; res = res->ai_next) {
	s = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (s < 0) {
	    warn("socket");
	    continue;
	}
	socket_set_reuseaddr(s, 1);
	socket_set_ipv6only(s, 1);

	if (bind(s, res->ai_addr, res->ai_addrlen) < 0) {
	    warn("bind");
	    close(s);
	    continue;
	}
	listen(s, 5);
	ret = heim_sipc_stream_listener(s, HEIM_SIPC_TYPE_HTTP,
					test_service, NULL, &u);
	if (ret)
	    errx(1, "heim_sipc_stream_listener: %d", ret);
    }
    freeaddrinfo(res0);
}