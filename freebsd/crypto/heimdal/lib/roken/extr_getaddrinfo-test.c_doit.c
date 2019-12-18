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
struct addrinfo {int ai_family; int ai_socktype; int ai_protocol; char* ai_canonname; int /*<<< orphan*/  ai_addr; struct addrinfo* ai_next; int /*<<< orphan*/  ai_flags; } ;
typedef  int /*<<< orphan*/  hints ;
typedef  int /*<<< orphan*/  addrstr ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ) ; 
 int family ; 
 int /*<<< orphan*/  flags ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int getaddrinfo (char const*,char const*,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/ * inet_ntop (int,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  socket_get_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_get_port (int /*<<< orphan*/ ) ; 
 int socktype ; 
 scalar_t__ verbose_counter ; 

__attribute__((used)) static void
doit (const char *nodename, const char *servname)
{
    struct addrinfo hints;
    struct addrinfo *res, *r;
    int ret;

    if (verbose_counter)
	printf ("(%s,%s)... ", nodename ? nodename : "null", servname);

    memset (&hints, 0, sizeof(hints));
    hints.ai_flags    = flags;
    hints.ai_family   = family;
    hints.ai_socktype = socktype;

    ret = getaddrinfo (nodename, servname, &hints, &res);
    if (ret)
	errx(1, "error: %s\n", gai_strerror(ret));

    if (verbose_counter)
	printf ("\n");

    for (r = res; r != NULL; r = r->ai_next) {
	char addrstr[256];

	if (inet_ntop (r->ai_family,
		       socket_get_address (r->ai_addr),
		       addrstr, sizeof(addrstr)) == NULL) {
	    if (verbose_counter)
		printf ("\tbad address?\n");
	    continue;
	}
	if (verbose_counter) {
	    printf ("\tfamily = %d, socktype = %d, protocol = %d, "
		    "address = \"%s\", port = %d",
		    r->ai_family, r->ai_socktype, r->ai_protocol,
		    addrstr,
		    ntohs(socket_get_port (r->ai_addr)));
	    if (r->ai_canonname)
		printf (", canonname = \"%s\"", r->ai_canonname);
	    printf ("\n");
	}
    }
    freeaddrinfo (res);
}