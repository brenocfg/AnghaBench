#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wpa_driver_ndis_data {int dummy; } ;
typedef  int /*<<< orphan*/  rkey ;
typedef  int /*<<< orphan*/  index ;
struct TYPE_3__ {int Length; int KeyIndex; int /*<<< orphan*/  BSSID; } ;
typedef  TYPE_1__ NDIS_802_11_REMOVE_KEY ;
typedef  int NDIS_802_11_KEY_INDEX ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  OID_802_11_REMOVE_KEY ; 
 int /*<<< orphan*/  OID_802_11_REMOVE_WEP ; 
 int ndis_set_oid (struct wpa_driver_ndis_data*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wpa_driver_ndis_remove_key(struct wpa_driver_ndis_data *drv,
				      int key_idx, const u8 *addr,
				      const u8 *bssid, int pairwise)
{
	NDIS_802_11_REMOVE_KEY rkey;
	NDIS_802_11_KEY_INDEX index;
	int res, res2;

	os_memset(&rkey, 0, sizeof(rkey));

	rkey.Length = sizeof(rkey);
	rkey.KeyIndex = key_idx;
	if (pairwise)
		rkey.KeyIndex |= 1 << 30;
	os_memcpy(rkey.BSSID, bssid, ETH_ALEN);

	res = ndis_set_oid(drv, OID_802_11_REMOVE_KEY, (char *) &rkey,
			   sizeof(rkey));
	if (!pairwise) {
		index = key_idx;
		res2 = ndis_set_oid(drv, OID_802_11_REMOVE_WEP,
				    (char *) &index, sizeof(index));
	} else
		res2 = 0;

	if (res < 0 && res2 < 0)
		return -1;
	return 0;
}