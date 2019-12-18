#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ const u8 ;
struct wpa_driver_ndis_data {int dummy; } ;
typedef  enum wpa_alg { ____Placeholder_wpa_alg } wpa_alg ;
typedef  size_t ULONGLONG ;
struct TYPE_4__ {size_t Length; int KeyIndex; size_t KeyLength; size_t KeyRSC; scalar_t__ const* KeyMaterial; scalar_t__ const* BSSID; } ;
typedef  TYPE_1__ NDIS_802_11_KEY ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int /*<<< orphan*/  OID_802_11_ADD_KEY ; 
 int WPA_ALG_NONE ; 
 int WPA_ALG_TKIP ; 
 int WPA_ALG_WEP ; 
 scalar_t__ is_broadcast_ether_addr (scalar_t__ const*) ; 
 int ndis_set_oid (struct wpa_driver_ndis_data*,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  os_free (TYPE_1__*) ; 
 int /*<<< orphan*/  os_memcpy (scalar_t__ const*,scalar_t__ const*,size_t) ; 
 int /*<<< orphan*/  os_memset (scalar_t__ const*,int,int) ; 
 TYPE_1__* os_zalloc (size_t) ; 
 int wpa_driver_ndis_add_wep (struct wpa_driver_ndis_data*,int,int,int,scalar_t__ const*,size_t) ; 
 scalar_t__ wpa_driver_ndis_get_bssid (struct wpa_driver_ndis_data*,scalar_t__ const*) ; 
 int wpa_driver_ndis_remove_key (struct wpa_driver_ndis_data*,int,scalar_t__ const*,scalar_t__ const*,int) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,scalar_t__ const*,size_t) ; 

__attribute__((used)) static int wpa_driver_ndis_set_key(const char *ifname, void *priv,
				   enum wpa_alg alg, const u8 *addr,
				   int key_idx, int set_tx,
				   const u8 *seq, size_t seq_len,
				   const u8 *key, size_t key_len)
{
	struct wpa_driver_ndis_data *drv = priv;
	size_t len, i;
	NDIS_802_11_KEY *nkey;
	int res, pairwise;
	u8 bssid[ETH_ALEN];

	if (addr == NULL || is_broadcast_ether_addr(addr)) {
		/* Group Key */
		pairwise = 0;
		if (wpa_driver_ndis_get_bssid(drv, bssid) < 0)
			os_memset(bssid, 0xff, ETH_ALEN);
	} else {
		/* Pairwise Key */
		pairwise = 1;
		os_memcpy(bssid, addr, ETH_ALEN);
	}

	if (alg == WPA_ALG_NONE || key_len == 0) {
		return wpa_driver_ndis_remove_key(drv, key_idx, addr, bssid,
						  pairwise);
	}

	if (alg == WPA_ALG_WEP) {
		return wpa_driver_ndis_add_wep(drv, pairwise, key_idx, set_tx,
					       key, key_len);
	}

	len = 12 + 6 + 6 + 8 + key_len;

	nkey = os_zalloc(len);
	if (nkey == NULL)
		return -1;

	nkey->Length = len;
	nkey->KeyIndex = key_idx;
	if (set_tx)
		nkey->KeyIndex |= 1 << 31;
	if (pairwise)
		nkey->KeyIndex |= 1 << 30;
	if (seq && seq_len)
		nkey->KeyIndex |= 1 << 29;
	nkey->KeyLength = key_len;
	os_memcpy(nkey->BSSID, bssid, ETH_ALEN);
	if (seq && seq_len) {
		for (i = 0; i < seq_len; i++)
			nkey->KeyRSC |= (ULONGLONG) seq[i] << (i * 8);
	}
	if (alg == WPA_ALG_TKIP && key_len == 32) {
		os_memcpy(nkey->KeyMaterial, key, 16);
		os_memcpy(nkey->KeyMaterial + 16, key + 24, 8);
		os_memcpy(nkey->KeyMaterial + 24, key + 16, 8);
	} else {
		os_memcpy(nkey->KeyMaterial, key, key_len);
	}

	wpa_hexdump_key(MSG_MSGDUMP, "NDIS: OID_802_11_ADD_KEY",
			(u8 *) nkey, len);
	res = ndis_set_oid(drv, OID_802_11_ADD_KEY, (char *) nkey, len);
	os_free(nkey);

	return res;
}