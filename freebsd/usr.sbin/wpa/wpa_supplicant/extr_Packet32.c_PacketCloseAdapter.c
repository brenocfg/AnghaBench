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
struct ifreq {int /*<<< orphan*/  ifr_flags; int /*<<< orphan*/  ifr_name; } ;
struct ieee80211req {int /*<<< orphan*/  i_val; int /*<<< orphan*/  i_type; int /*<<< orphan*/  i_name; } ;
struct adapter {int /*<<< orphan*/  socket; int /*<<< orphan*/  name; int /*<<< orphan*/  prev_roaming; } ;
typedef  int /*<<< orphan*/  ireq ;
typedef  int /*<<< orphan*/  ifr ;
typedef  struct ieee80211req* caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_IOC_ROAMING ; 
 int /*<<< orphan*/  IFF_UP ; 
 int /*<<< orphan*/  SIOCGIFFLAGS ; 
 int /*<<< orphan*/  SIOCS80211 ; 
 int /*<<< orphan*/  SIOCSIFFLAGS ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct adapter*) ; 
 int /*<<< orphan*/  ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ieee80211req*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
PacketCloseAdapter(void *iface)
{	
	struct adapter		*a;
	struct ifreq		ifr;
	struct ieee80211req	ireq;

	if (iface == NULL)
		return;

	a = iface;

	/* Reset net80211 roaming */
	bzero((char *)&ireq, sizeof(ireq));
	strncpy(ireq.i_name, a->name, sizeof (ifr.ifr_name));
	ireq.i_type = IEEE80211_IOC_ROAMING;
	ireq.i_val = a->prev_roaming;
	ioctl(a->socket, SIOCS80211, &ireq);

	bzero((char *)&ifr, sizeof(ifr));
        strncpy(ifr.ifr_name, a->name, sizeof (ifr.ifr_name));
        ioctl(a->socket, SIOCGIFFLAGS, (caddr_t)&ifr);
        ifr.ifr_flags &= ~IFF_UP;
        ioctl(a->socket, SIOCSIFFLAGS, (caddr_t)&ifr);
	close(a->socket);
	free(a);

	return;
}