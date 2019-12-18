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
struct iftot {int /*<<< orphan*/  ift_co; int /*<<< orphan*/  ift_ob; int /*<<< orphan*/  ift_od; int /*<<< orphan*/  ift_oe; int /*<<< orphan*/  ift_op; int /*<<< orphan*/  ift_ib; int /*<<< orphan*/  ift_id; int /*<<< orphan*/  ift_ie; int /*<<< orphan*/  ift_ip; } ;
struct ifaddrs {int /*<<< orphan*/  ifa_name; TYPE_1__* ifa_addr; struct ifaddrs* ifa_next; } ;
struct TYPE_2__ {scalar_t__ sa_family; } ;

/* Variables and functions */
 scalar_t__ AF_LINK ; 
 int /*<<< orphan*/  EX_DATAERR ; 
 int /*<<< orphan*/  EX_OSERR ; 
 scalar_t__ IFA_STAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct iftot*,int) ; 
 int /*<<< orphan*/  collisions ; 
 int /*<<< orphan*/  freeifaddrs (struct ifaddrs*) ; 
 scalar_t__ getifaddrs (struct ifaddrs**) ; 
 int /*<<< orphan*/  ibytes ; 
 int /*<<< orphan*/  ierrors ; 
 scalar_t__ interface ; 
 int /*<<< orphan*/  ipackets ; 
 int /*<<< orphan*/  iqdrops ; 
 int /*<<< orphan*/  obytes ; 
 int /*<<< orphan*/  oerrors ; 
 int /*<<< orphan*/  opackets ; 
 int /*<<< orphan*/  oqdrops ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  xo_err (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void
fill_iftot(struct iftot *st)
{
	struct ifaddrs *ifap, *ifa;
	bool found = false;

	if (getifaddrs(&ifap) != 0)
		xo_err(EX_OSERR, "getifaddrs");

	bzero(st, sizeof(*st));

	for (ifa = ifap; ifa; ifa = ifa->ifa_next) {
		if (ifa->ifa_addr->sa_family != AF_LINK)
			continue;
		if (interface) {
			if (strcmp(ifa->ifa_name, interface) == 0)
				found = true;
			else
				continue;
		}

		st->ift_ip += IFA_STAT(ipackets);
		st->ift_ie += IFA_STAT(ierrors);
		st->ift_id += IFA_STAT(iqdrops);
		st->ift_ib += IFA_STAT(ibytes);
		st->ift_op += IFA_STAT(opackets);
		st->ift_oe += IFA_STAT(oerrors);
		st->ift_od += IFA_STAT(oqdrops);
		st->ift_ob += IFA_STAT(obytes);
 		st->ift_co += IFA_STAT(collisions);
	}

	if (interface && found == false)
		xo_err(EX_DATAERR, "interface %s not found", interface);

	freeifaddrs(ifap);
}