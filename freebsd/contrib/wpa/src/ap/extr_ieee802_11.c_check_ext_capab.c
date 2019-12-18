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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sta_info {int qos_map_enabled; int ecsa_supported; size_t* ext_capability; } ;
struct hostapd_data {int dummy; } ;

/* Variables and functions */
 int const BIT (int) ; 
 int /*<<< orphan*/  WLAN_STATUS_SUCCESS ; 
 int /*<<< orphan*/  os_free (size_t*) ; 
 size_t* os_malloc (int) ; 
 int /*<<< orphan*/  os_memcpy (size_t*,int const*,size_t) ; 

__attribute__((used)) static u16 check_ext_capab(struct hostapd_data *hapd, struct sta_info *sta,
			   const u8 *ext_capab_ie, size_t ext_capab_ie_len)
{
#ifdef CONFIG_INTERWORKING
	/* check for QoS Map support */
	if (ext_capab_ie_len >= 5) {
		if (ext_capab_ie[4] & 0x01)
			sta->qos_map_enabled = 1;
	}
#endif /* CONFIG_INTERWORKING */

	if (ext_capab_ie_len > 0) {
		sta->ecsa_supported = !!(ext_capab_ie[0] & BIT(2));
		os_free(sta->ext_capability);
		sta->ext_capability = os_malloc(1 + ext_capab_ie_len);
		if (sta->ext_capability) {
			sta->ext_capability[0] = ext_capab_ie_len;
			os_memcpy(sta->ext_capability + 1, ext_capab_ie,
				  ext_capab_ie_len);
		}
	}

	return WLAN_STATUS_SUCCESS;
}