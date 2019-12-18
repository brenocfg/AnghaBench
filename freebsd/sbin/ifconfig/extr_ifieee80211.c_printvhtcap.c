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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u_int8_t ;
struct TYPE_2__ {int /*<<< orphan*/  tx_highest; int /*<<< orphan*/  tx_mcs_map; int /*<<< orphan*/  rx_highest; int /*<<< orphan*/  rx_mcs_map; } ;
struct ieee80211_ie_vhtcap {TYPE_1__ supp_mcs; int /*<<< orphan*/  vht_cap_info; } ;

/* Variables and functions */
 int LE_READ_2 (int /*<<< orphan*/ *) ; 
 int LE_READ_4 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static void
printvhtcap(const char *tag, const u_int8_t *ie, size_t ielen, int maxlen)
{
	printf("%s", tag);
	if (verbose) {
		const struct ieee80211_ie_vhtcap *vhtcap =
		    (const struct ieee80211_ie_vhtcap *) ie;
		uint32_t vhtcap_info = LE_READ_4(&vhtcap->vht_cap_info);

		printf("<cap 0x%08x", vhtcap_info);
		printf(" rx_mcs_map 0x%x",
		    LE_READ_2(&vhtcap->supp_mcs.rx_mcs_map));
		printf(" rx_highest %d",
		    LE_READ_2(&vhtcap->supp_mcs.rx_highest) & 0x1fff);
		printf(" tx_mcs_map 0x%x",
		    LE_READ_2(&vhtcap->supp_mcs.tx_mcs_map));
		printf(" tx_highest %d",
		    LE_READ_2(&vhtcap->supp_mcs.tx_highest) & 0x1fff);

		printf(">");
	}
}