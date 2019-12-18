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
struct in6_ndifreq {unsigned int ifindex; int /*<<< orphan*/  ifname; } ;
typedef  int /*<<< orphan*/  ndifreq ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_2__ {int /*<<< orphan*/  ifr_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIOCGDEFIFACE_IN6 ; 
 unsigned int if_nametoindex (int /*<<< orphan*/ ) ; 
 TYPE_1__ ifr ; 
 int ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct in6_ndifreq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static int
isnd6defif(int s)
{
	struct in6_ndifreq ndifreq;
	unsigned int ifindex;
	int error;

	memset(&ndifreq, 0, sizeof(ndifreq));
	strlcpy(ndifreq.ifname, ifr.ifr_name, sizeof(ndifreq.ifname));

	ifindex = if_nametoindex(ndifreq.ifname);
	error = ioctl(s, SIOCGDEFIFACE_IN6, (caddr_t)&ndifreq);
	if (error) {
		warn("ioctl(SIOCGDEFIFACE_IN6)");
		return (error);
	}
	return (ndifreq.ifindex == ifindex);
}