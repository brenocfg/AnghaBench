#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct ifreq {int /*<<< orphan*/  ifr_name; } ;
struct ifaddrs {int ifa_flags; TYPE_2__* ifa_addr; int /*<<< orphan*/  ifa_name; struct ifaddrs* ifa_next; } ;
typedef  int /*<<< orphan*/  in_addr_t ;
typedef  int /*<<< orphan*/  ifr ;
struct TYPE_4__ {scalar_t__ sa_family; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIOCSETIF ; 
 scalar_t__ ENOENT ; 
 int IFF_LOOPBACK ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  atf_tc_skip (char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  freeifaddrs (struct ifaddrs*) ; 
 int getifaddrs (struct ifaddrs**) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct ifreq*) ; 
 int /*<<< orphan*/  memset (struct ifreq*,int /*<<< orphan*/ ,int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
open_lobpf(in_addr_t *addrp)
{
	struct ifreq ifr;
	struct ifaddrs *ifa, *ifap;
	int error, fd;

	fd = open("/dev/bpf0", O_RDWR);
	if (fd < 0 && errno == ENOENT)
		atf_tc_skip("no BPF device available");
	ATF_REQUIRE_MSG(fd >= 0, "open(/dev/bpf0): %s", strerror(errno));

	error = getifaddrs(&ifap);
	ATF_REQUIRE(error == 0);
	for (ifa = ifap; ifa != NULL; ifa = ifa->ifa_next)
		if ((ifa->ifa_flags & IFF_LOOPBACK) != 0 &&
		    ifa->ifa_addr->sa_family == AF_INET)
			break;
	if (ifa == NULL)
		atf_tc_skip("no loopback address found");

	memset(&ifr, 0, sizeof(ifr));
	strlcpy(ifr.ifr_name, ifa->ifa_name, IFNAMSIZ);
	error = ioctl(fd, BIOCSETIF, &ifr);
	ATF_REQUIRE_MSG(error == 0, "ioctl(BIOCSETIF): %s", strerror(errno));

	*addrp = ((struct sockaddr_in *)(void *)ifa->ifa_addr)->sin_addr.s_addr;

	freeifaddrs(ifap);

	return (fd);
}