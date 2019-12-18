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
typedef  int /*<<< orphan*/  ifr ;
struct TYPE_2__ {struct ifreq ireq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_IOC_CHANNEL ; 
 unsigned int IFF_PPROMISC ; 
 unsigned int IFF_UP ; 
 int /*<<< orphan*/  SIOCGIFFLAGS ; 
 int /*<<< orphan*/  SIOCSIFFLAGS ; 
 TYPE_1__ chaninfo ; 
 int /*<<< orphan*/  die (int,char*) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ifreq*) ; 
 int /*<<< orphan*/  ioctl_s ; 
 int /*<<< orphan*/  memset (struct ifreq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_chan (int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

void setup_if(char *dev) {
        struct ifreq ifr;
        unsigned int flags;

        // set chan
        memset(&chaninfo.ireq, 0, sizeof(chaninfo.ireq));
        strcpy(chaninfo.ireq.i_name, dev);
        chaninfo.ireq.i_type = IEEE80211_IOC_CHANNEL;

        set_chan(1);

        // set iface up and promisc
        memset(&ifr, 0, sizeof(ifr));
        strcpy(ifr.ifr_name, dev);
        if (ioctl(ioctl_s, SIOCGIFFLAGS, &ifr) == -1)
                die(1, "ioctl(SIOCGIFFLAGS)");
        
        flags = (ifr.ifr_flags & 0xffff) | (ifr.ifr_flagshigh << 16);
        flags |= IFF_UP | IFF_PPROMISC;
        
        memset(&ifr, 0, sizeof(ifr));
        strcpy(ifr.ifr_name, dev);
        ifr.ifr_flags = flags & 0xffff;
        ifr.ifr_flagshigh = flags >> 16;
        if (ioctl(ioctl_s, SIOCSIFFLAGS, &ifr) == -1)
                die(1, "ioctl(SIOCSIFFLAGS)");
}