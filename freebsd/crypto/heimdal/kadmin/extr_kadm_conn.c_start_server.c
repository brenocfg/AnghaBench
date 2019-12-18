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
struct kadm_port {char* port; int def_port; struct kadm_port* next; } ;
struct addrinfo {int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; struct addrinfo* ai_next; int /*<<< orphan*/  ai_flags; } ;
typedef  int /*<<< orphan*/  portstr ;
typedef  int /*<<< orphan*/  krb5_socket_t ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  hints ;

/* Variables and functions */
 int /*<<< orphan*/  AI_PASSIVE ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOMAXCONN ; 
 int /*<<< orphan*/  bind (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int getaddrinfo (int /*<<< orphan*/ *,char*,struct addrinfo*,struct addrinfo**) ; 
 struct kadm_port* kadm_ports ; 
 int /*<<< orphan*/  krb5_eai_to_heim_errno (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_errx (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  krb5_warn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  krb5_warnx (int /*<<< orphan*/ ,char*,unsigned long) ; 
 int /*<<< orphan*/  listen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  parse_ports (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * realloc (int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ rk_IS_BAD_SOCKET (int /*<<< orphan*/ ) ; 
 scalar_t__ rk_IS_SOCKET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rk_SOCK_ERRNO ; 
 int /*<<< orphan*/  rk_closesocket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_set_ipv6only (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  socket_set_reuseaddr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wait_for_connection (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 

void
start_server(krb5_context contextp, const char *port_str)
{
    int e;
    struct kadm_port *p;

    krb5_socket_t *socks = NULL, *tmp;
    unsigned int num_socks = 0;
    int i;

    if (port_str == NULL)
	port_str = "+";

    parse_ports(contextp, port_str);

    for(p = kadm_ports; p; p = p->next) {
	struct addrinfo hints, *ai, *ap;
	char portstr[32];
	memset (&hints, 0, sizeof(hints));
	hints.ai_flags    = AI_PASSIVE;
	hints.ai_socktype = SOCK_STREAM;

	e = getaddrinfo(NULL, p->port, &hints, &ai);
	if(e) {
	    snprintf(portstr, sizeof(portstr), "%u", p->def_port);
	    e = getaddrinfo(NULL, portstr, &hints, &ai);
	}

	if(e) {
	    krb5_warn(contextp, krb5_eai_to_heim_errno(e, errno),
		      "%s", portstr);
	    continue;
	}
	i = 0;
	for(ap = ai; ap; ap = ap->ai_next)
	    i++;
	tmp = realloc(socks, (num_socks + i) * sizeof(*socks));
	if(tmp == NULL) {
	    krb5_warnx(contextp, "failed to reallocate %lu bytes",
		       (unsigned long)(num_socks + i) * sizeof(*socks));
	    continue;
	}
	socks = tmp;
	for(ap = ai; ap; ap = ap->ai_next) {
	    krb5_socket_t s = socket(ap->ai_family, ap->ai_socktype, ap->ai_protocol);
	    if(rk_IS_BAD_SOCKET(s)) {
		krb5_warn(contextp, rk_SOCK_ERRNO, "socket");
		continue;
	    }

	    socket_set_reuseaddr(s, 1);
	    socket_set_ipv6only(s, 1);

	    if (rk_IS_SOCKET_ERROR(bind (s, ap->ai_addr, ap->ai_addrlen))) {
		krb5_warn(contextp, rk_SOCK_ERRNO, "bind");
		rk_closesocket(s);
		continue;
	    }
	    if (rk_IS_SOCKET_ERROR(listen (s, SOMAXCONN))) {
		krb5_warn(contextp, rk_SOCK_ERRNO, "listen");
		rk_closesocket(s);
		continue;
	    }
	    socks[num_socks++] = s;
	}
	freeaddrinfo (ai);
    }
    if(num_socks == 0)
	krb5_errx(contextp, 1, "no sockets to listen to - exiting");

    wait_for_connection(contextp, socks, num_socks);
}