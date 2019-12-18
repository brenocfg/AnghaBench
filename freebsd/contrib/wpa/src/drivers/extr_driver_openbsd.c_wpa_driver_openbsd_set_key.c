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
typedef  int /*<<< orphan*/  u8 ;
struct openbsd_driver_data {int /*<<< orphan*/  sock; int /*<<< orphan*/  ifname; } ;
struct ieee80211_keyavail {int /*<<< orphan*/  i_key; int /*<<< orphan*/  i_macaddr; int /*<<< orphan*/  i_name; } ;
typedef  int /*<<< orphan*/  keyavail ;
typedef  enum wpa_alg { ____Placeholder_wpa_alg } wpa_alg ;

/* Variables and functions */
 size_t IEEE80211_PMK_LEN ; 
 int /*<<< orphan*/  SIOCS80211KEYAVAIL ; 
 int WPA_ALG_PMK ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ieee80211_keyavail*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  memset (struct ieee80211_keyavail*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ wpa_driver_openbsd_get_bssid (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
wpa_driver_openbsd_set_key(const char *ifname, void *priv, enum wpa_alg alg,
	    const unsigned char *addr, int key_idx, int set_tx, const u8 *seq,
	    size_t seq_len, const u8 *key, size_t key_len)
{
	struct openbsd_driver_data *drv = priv;
	struct ieee80211_keyavail keyavail;

	if (alg != WPA_ALG_PMK || key_len > IEEE80211_PMK_LEN)
		return -1;

	memset(&keyavail, 0, sizeof(keyavail));
	os_strlcpy(keyavail.i_name, drv->ifname, sizeof(keyavail.i_name));
	if (wpa_driver_openbsd_get_bssid(priv, keyavail.i_macaddr) < 0)
		return -1;
	memcpy(keyavail.i_key, key, key_len);

	if (ioctl(drv->sock, SIOCS80211KEYAVAIL, &keyavail) < 0)
		return -1;

	return 0;
}