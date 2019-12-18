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
typedef  int /*<<< orphan*/  uint32_t ;
struct iwi_softc {int dummy; } ;
struct ieee80211vap {int iv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int IEEE80211_F_PMGTON ; 
 int /*<<< orphan*/  IWI_CMD_SET_POWER_MODE ; 
 int /*<<< orphan*/  IWI_POWER_MODE_CAM ; 
 int /*<<< orphan*/  IWI_POWER_MODE_MAX ; 
 int /*<<< orphan*/  htole32 (int /*<<< orphan*/ ) ; 
 int iwi_cmd (struct iwi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  le32toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iwi_setpowermode(struct iwi_softc *sc, struct ieee80211vap *vap)
{
	uint32_t data;

	if (vap->iv_flags & IEEE80211_F_PMGTON) {
		/* XXX set more fine-grained operation */
		data = htole32(IWI_POWER_MODE_MAX);
	} else
		data = htole32(IWI_POWER_MODE_CAM);

	DPRINTF(("Setting power mode to %u\n", le32toh(data)));
	return iwi_cmd(sc, IWI_CMD_SET_POWER_MODE, &data, sizeof data);
}