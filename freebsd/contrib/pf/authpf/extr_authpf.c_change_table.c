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
struct TYPE_2__ {int /*<<< orphan*/  pfrt_name; } ;
struct pfr_addr {int pfrio_esize; int pfrio_size; int pfra_net; void* pfra_af; int /*<<< orphan*/  pfra_ip6addr; int /*<<< orphan*/  pfra_ip4addr; struct pfr_addr* pfrio_buffer; TYPE_1__ pfrio_table; } ;
struct pfioc_table {int pfrio_esize; int pfrio_size; int pfra_net; void* pfra_af; int /*<<< orphan*/  pfra_ip6addr; int /*<<< orphan*/  pfra_ip4addr; struct pfioc_table* pfrio_buffer; TYPE_1__ pfrio_table; } ;
typedef  int /*<<< orphan*/  io ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 void* AF_INET ; 
 void* AF_INET6 ; 
 int /*<<< orphan*/  DIOCRADDADDRS ; 
 int /*<<< orphan*/  DIOCRDELADDRS ; 
 scalar_t__ ESRCH ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  bzero (struct pfr_addr*,int) ; 
 int /*<<< orphan*/  dev ; 
 scalar_t__ errno ; 
 int inet_pton (void*,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pfr_addr*) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  tablename ; 

__attribute__((used)) static int
change_table(int add, const char *ip_src)
{
	struct pfioc_table	io;
	struct pfr_addr		addr;

	bzero(&io, sizeof(io));
	strlcpy(io.pfrio_table.pfrt_name, tablename,
	    sizeof(io.pfrio_table.pfrt_name));
	io.pfrio_buffer = &addr;
	io.pfrio_esize = sizeof(addr);
	io.pfrio_size = 1;

	bzero(&addr, sizeof(addr));
	if (ip_src == NULL || !ip_src[0])
		return (-1);
	if (inet_pton(AF_INET, ip_src, &addr.pfra_ip4addr) == 1) {
		addr.pfra_af = AF_INET;
		addr.pfra_net = 32;
	} else if (inet_pton(AF_INET6, ip_src, &addr.pfra_ip6addr) == 1) {
		addr.pfra_af = AF_INET6;
		addr.pfra_net = 128;
	} else {
		syslog(LOG_ERR, "invalid ipsrc");
		return (-1);
	}

	if (ioctl(dev, add ? DIOCRADDADDRS : DIOCRDELADDRS, &io) &&
	    errno != ESRCH) {
		syslog(LOG_ERR, "cannot %s %s from table %s: %s",
		    add ? "add" : "remove", ip_src, tablename,
		    strerror(errno));
		return (-1);
	}
	return (0);
}