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
struct ifreq {int ifr_flags; int ifr_flagshigh; int /*<<< orphan*/  ifr_name; int /*<<< orphan*/  i_type; int /*<<< orphan*/  i_name; } ;
struct ifmediareq {int dummy; } ;
typedef  int /*<<< orphan*/  ifr ;
struct TYPE_2__ {int s; scalar_t__ chan; struct ifreq ireq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_IOC_CHANNEL ; 
 unsigned int IFF_PPROMISC ; 
 unsigned int IFF_UP ; 
 scalar_t__ IFNAMSIZ ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SIOCGIFFLAGS ; 
 int /*<<< orphan*/  SIOCSIFFLAGS ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 TYPE_1__ chaninfo ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct ifreq*) ; 
 int /*<<< orphan*/  memset (struct ifreq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mymac ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  set_chan (int) ; 
 int /*<<< orphan*/  set_if_mac (int /*<<< orphan*/ ,char*) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  time_print (char*,...) ; 

void setup_if(char *dev) {
	int s;
	struct ifreq ifr;
	unsigned int flags;
	struct ifmediareq ifmr;
	int *mwords;

	if(strlen(dev) >= IFNAMSIZ) {
		time_print("Interface name too long...\n");
		exit(1);
	}

	time_print("Setting up %s... ", dev);
	fflush(stdout);
	
	set_if_mac(mymac, dev);

	s = socket(PF_INET, SOCK_DGRAM, 0);
	if (s == -1) {
		perror("socket()");
		exit(1);
	}

	// set chan
	memset(&chaninfo.ireq, 0, sizeof(chaninfo.ireq));
	strcpy(chaninfo.ireq.i_name, dev);
	chaninfo.ireq.i_type = IEEE80211_IOC_CHANNEL;
	
	chaninfo.chan = 0;
	chaninfo.s = s;
	set_chan(1);

	// set iface up and promisc
	memset(&ifr, 0, sizeof(ifr));
	strcpy(ifr.ifr_name, dev);
	if (ioctl(s, SIOCGIFFLAGS, &ifr) == -1) {
		perror("ioctl(SIOCGIFFLAGS)");
		exit(1);
	}

	flags = (ifr.ifr_flags & 0xffff) | (ifr.ifr_flagshigh << 16);
	flags |= IFF_UP | IFF_PPROMISC;
	
	memset(&ifr, 0, sizeof(ifr));
	strcpy(ifr.ifr_name, dev);
	ifr.ifr_flags = flags & 0xffff;
	ifr.ifr_flagshigh = flags >> 16;
	if (ioctl(s, SIOCSIFFLAGS, &ifr) == -1) {
		perror("ioctl(SIOCSIFFLAGS)");
		exit(1);
	}

	printf("done\n");
}