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
struct ifreq {int ifr_flags; int ifr_flagshigh; int /*<<< orphan*/  ifr_name; } ;
struct ifnet {int if_flags; int (* if_ioctl ) (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  if_xname; } ;
struct hn_softc {struct ifnet* hn_vf_ifp; } ;
typedef  int /*<<< orphan*/  ifr ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  HN_LOCK_ASSERT (struct hn_softc*) ; 
 int /*<<< orphan*/  SIOCSIFFLAGS ; 
 int /*<<< orphan*/  memset (struct ifreq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hn_xpnt_vf_iocsetflags(struct hn_softc *sc)
{
	struct ifnet *vf_ifp;
	struct ifreq ifr;

	HN_LOCK_ASSERT(sc);
	vf_ifp = sc->hn_vf_ifp;

	memset(&ifr, 0, sizeof(ifr));
	strlcpy(ifr.ifr_name, vf_ifp->if_xname, sizeof(ifr.ifr_name));
	ifr.ifr_flags = vf_ifp->if_flags & 0xffff;
	ifr.ifr_flagshigh = vf_ifp->if_flags >> 16;
	return (vf_ifp->if_ioctl(vf_ifp, SIOCSIFFLAGS, (caddr_t)&ifr));
}