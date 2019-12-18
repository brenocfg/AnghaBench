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
typedef  int uint32_t ;
struct sockaddr_dl {int sdl_len; int sdl_alen; scalar_t__ sdl_family; int /*<<< orphan*/  ifr_addr; int /*<<< orphan*/ * ifr_name; } ;
struct ifreq {int sdl_len; int sdl_alen; scalar_t__ sdl_family; int /*<<< orphan*/  ifr_addr; int /*<<< orphan*/ * ifr_name; } ;
struct ifmaddrs {int /*<<< orphan*/ * ifma_name; scalar_t__ ifma_addr; struct ifmaddrs* ifma_next; } ;
struct ether_addr {int* octet; } ;
struct TYPE_3__ {scalar_t__ sa_family; } ;
struct TYPE_4__ {struct sockaddr_dl sdl; TYPE_1__ sa; } ;
typedef  TYPE_2__ sockunion_t ;

/* Variables and functions */
 scalar_t__ AF_LINK ; 
 scalar_t__ ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  LLADDR (struct sockaddr_dl*) ; 
 int /*<<< orphan*/  SIOCADDMULTI ; 
 int /*<<< orphan*/  SIOCDELMULTI ; 
 scalar_t__ bcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ dorandom ; 
 struct ether_addr* ether_aton (char*) ; 
 int /*<<< orphan*/  ether_ntoa (struct ether_addr*) ; 
 int /*<<< orphan*/  freeifmaddrs (struct ifmaddrs*) ; 
 scalar_t__ getifmaddrs (struct ifmaddrs**) ; 
 int /*<<< orphan*/  ifname ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct sockaddr_dl*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct ether_addr*,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_dl*,int /*<<< orphan*/ ,int) ; 
 int random () ; 
 int /*<<< orphan*/  srandomdev () ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test_ether_multi(int sock)
{
	struct ifreq ifr;
	struct sockaddr_dl *dlp;
	struct ether_addr ea;
	struct ifmaddrs *ifma, *ifmap;
	int found;

	/* Choose an 802 multicast address. */
	if (dorandom) {
		uint32_t mac4;

		srandomdev();
		mac4 = random();
		ea.octet[0] = 0x01;
		ea.octet[1] = 0x80;
		ea.octet[2] = ((mac4 >> 24 & 0xFF));
		ea.octet[3] = ((mac4 >> 16 & 0xFF));
		ea.octet[4] = ((mac4 >> 8 & 0xFF));
		ea.octet[5] = (mac4 & 0xFF);
	} else {
		struct ether_addr *nep = ether_aton("01:80:DE:FA:CA:7E");
		ea = *nep;
	}

	/* Fill out ifreq, and fill out 802 group address. */
	memset(&ifr, 0, sizeof(struct ifreq));
	strlcpy(&ifr.ifr_name[0], ifname, IFNAMSIZ);
	dlp = (struct sockaddr_dl *)&ifr.ifr_addr;
	memset(dlp, 0, sizeof(struct sockaddr_dl));
	dlp->sdl_len = sizeof(struct sockaddr_dl);
	dlp->sdl_family = AF_LINK;
	dlp->sdl_alen = sizeof(struct ether_addr);
	memcpy(LLADDR(dlp), &ea, sizeof(struct ether_addr));

	/* Join an 802 group. */
	if (ioctl(sock, SIOCADDMULTI, &ifr) < 0) {
		warn("can't add ethernet multicast membership");
		return;
	}

	/* Check that we joined the group by calling getifmaddrs(). */
	found = 0;
	if (getifmaddrs(&ifmap) != 0) {
		warn("getifmaddrs()");
	} else {
		for (ifma = ifmap; ifma; ifma = ifma->ifma_next) {
			sockunion_t *psa = (sockunion_t *)ifma->ifma_addr;
			if (ifma->ifma_name == NULL || psa == NULL)
				continue;

			if (psa->sa.sa_family != AF_LINK ||
			    psa->sdl.sdl_alen != ETHER_ADDR_LEN)
				continue;

			if (bcmp(LLADDR(&psa->sdl), LLADDR(dlp),
			    ETHER_ADDR_LEN) == 0) {
				found = 1;
				break;
			}
		}
		freeifmaddrs(ifmap);
	}
	if (!found) {
		warnx("group membership for %s not returned by getifmaddrs()",
		   ether_ntoa(&ea));
	}

	/* Fill out ifreq, and fill out 802 group address. */
	memset(&ifr, 0, sizeof(struct ifreq));
	strlcpy(&ifr.ifr_name[0], ifname, IFNAMSIZ);
	dlp = (struct sockaddr_dl *)&ifr.ifr_addr;
	memset(dlp, 0, sizeof(struct sockaddr_dl));
	dlp->sdl_len = sizeof(struct sockaddr_dl);
	dlp->sdl_family = AF_LINK;
	dlp->sdl_alen = sizeof(struct ether_addr);
	memcpy(LLADDR(dlp), &ea, sizeof(struct ether_addr));

	/* Leave an 802 group. */
	if (ioctl(sock, SIOCDELMULTI, &ifr) < 0)
		warn("can't delete ethernet multicast membership");

}