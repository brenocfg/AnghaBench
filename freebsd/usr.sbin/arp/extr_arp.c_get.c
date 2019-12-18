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
struct sockaddr_in {TYPE_1__ sin_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARP_XO_VERSION ; 
 struct sockaddr_in* getaddr (char*) ; 
 int /*<<< orphan*/  inet_ntoa (TYPE_1__) ; 
 int /*<<< orphan*/  print_entry ; 
 int /*<<< orphan*/  rifname ; 
 int search (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xo_close_container (char*) ; 
 int /*<<< orphan*/  xo_close_list (char*) ; 
 int /*<<< orphan*/  xo_emit (char*,...) ; 
 int /*<<< orphan*/  xo_finish () ; 
 int /*<<< orphan*/  xo_open_container (char*) ; 
 int /*<<< orphan*/  xo_open_list (char*) ; 
 int /*<<< orphan*/  xo_set_version (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
get(char *host)
{
	struct sockaddr_in *addr;
	int found;

	addr = getaddr(host);
	if (addr == NULL)
		return (1);

	xo_set_version(ARP_XO_VERSION);
	xo_open_container("arp");
	xo_open_list("arp-cache");

	found = search(addr->sin_addr.s_addr, print_entry);

	if (found == 0) {
		xo_emit("{d:hostname/%s} ({d:ip-address/%s}) -- no entry",
		    host, inet_ntoa(addr->sin_addr));
		if (rifname)
			xo_emit(" on {d:interface/%s}", rifname);
		xo_emit("\n");
	}

	xo_close_list("arp-cache");
	xo_close_container("arp");
	xo_finish();

	return (found == 0);
}