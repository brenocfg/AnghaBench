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
struct ifreq {int /*<<< orphan*/  ifr_media; int /*<<< orphan*/  ifm_current; int /*<<< orphan*/  ifr_name; int /*<<< orphan*/  ifm_name; } ;
struct ifmediareq {int /*<<< orphan*/  ifr_media; int /*<<< orphan*/  ifm_current; int /*<<< orphan*/  ifr_name; int /*<<< orphan*/  ifm_name; } ;
struct TYPE_4__ {int mode; TYPE_1__* ifp; } ;
struct atmif_priv {TYPE_2__ pub; } ;
typedef  int /*<<< orphan*/  ifr ;
typedef  int /*<<< orphan*/  ifmr ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ATMIF_SUNI_MODE_SDH ; 
 int /*<<< orphan*/  IFM_ATM_SDH ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  SIOCGIFMEDIA ; 
 int /*<<< orphan*/  SIOCSIFMEDIA ; 
 int SNMP_ERR_GENERR ; 
 int SNMP_ERR_NOERROR ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ifreq*) ; 
 int /*<<< orphan*/  memset (struct ifreq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mib_netsock ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
atmif_set_mode(struct atmif_priv *aif, int newmode)
{
	struct ifmediareq ifmr;
	struct ifreq ifr;

	memset(&ifmr, 0, sizeof(ifmr));
	strcpy(ifmr.ifm_name, aif->pub.ifp->name);

	/* get current mode */
	if (ioctl(mib_netsock, SIOCGIFMEDIA, &ifmr) < 0) {
		syslog(LOG_ERR, "SIOCGIFMEDIA: %m");
		return (SNMP_ERR_GENERR);
	}

	memset(&ifr, 0, sizeof(ifr));
	strcpy(ifr.ifr_name, aif->pub.ifp->name);

	ifr.ifr_media = ifmr.ifm_current;
	if (newmode == ATMIF_SUNI_MODE_SDH)
		ifr.ifr_media |= IFM_ATM_SDH;
	else
		ifr.ifr_media &= ~IFM_ATM_SDH;

	if (ioctl(mib_netsock, SIOCSIFMEDIA, &ifr) < 0) {
		syslog(LOG_ERR, "SIOCSIFMEDIA: %m");
		return (SNMP_ERR_GENERR);
	}

	aif->pub.mode = newmode;
	return (SNMP_ERR_NOERROR);
}