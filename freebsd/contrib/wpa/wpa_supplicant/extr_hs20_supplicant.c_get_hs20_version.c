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
struct wpa_bss {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HS20_IE_VENDOR_TYPE ; 
 int* wpa_bss_get_vendor_ie (struct wpa_bss*,int /*<<< orphan*/ ) ; 

int get_hs20_version(struct wpa_bss *bss)
{
	const u8 *ie;

	if (!bss)
		return 0;

	ie = wpa_bss_get_vendor_ie(bss, HS20_IE_VENDOR_TYPE);
	if (!ie || ie[1] < 5)
		return 0;

	return ((ie[6] >> 4) & 0x0f) + 1;
}