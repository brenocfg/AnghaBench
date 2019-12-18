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
struct ifmediareq {int ifm_current; int /*<<< orphan*/  ifm_name; } ;
struct TYPE_4__ {int /*<<< orphan*/  mode; TYPE_1__* ifp; } ;
struct atmif_priv {TYPE_2__ pub; } ;
typedef  int /*<<< orphan*/  ifmr ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMIF_SUNI_MODE_SDH ; 
 int /*<<< orphan*/  ATMIF_SUNI_MODE_SONET ; 
 int /*<<< orphan*/  ATMIF_SUNI_MODE_UNKNOWN ; 
 int IFM_ATM_SDH ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  SIOCGIFMEDIA ; 
 int SNMP_ERR_GENERR ; 
 int SNMP_ERR_NOERROR ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ifmediareq*) ; 
 int /*<<< orphan*/  memset (struct ifmediareq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mib_netsock ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
atmif_get_mode(struct atmif_priv *aif)
{
	struct ifmediareq ifmr;

	memset(&ifmr, 0, sizeof(ifmr));
	strcpy(ifmr.ifm_name, aif->pub.ifp->name);

	if (ioctl(mib_netsock, SIOCGIFMEDIA, &ifmr) < 0) {
		syslog(LOG_ERR, "SIOCGIFMEDIA: %m");
		aif->pub.mode = ATMIF_SUNI_MODE_UNKNOWN;
		return (SNMP_ERR_GENERR);
	}
	if (ifmr.ifm_current & IFM_ATM_SDH)
		aif->pub.mode = ATMIF_SUNI_MODE_SDH;
	else
		aif->pub.mode = ATMIF_SUNI_MODE_SONET;

	return (SNMP_ERR_NOERROR);
}