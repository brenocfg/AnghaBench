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
struct wpa_scan_res {size_t ie_len; size_t beacon_ie_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  const* get_ie (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ) ; 

const u8 * wpa_scan_get_ie(const struct wpa_scan_res *res, u8 ie)
{
	size_t ie_len = res->ie_len;

	/* Use the Beacon frame IEs if res->ie_len is not available */
	if (!ie_len)
		ie_len = res->beacon_ie_len;

	return get_ie((const u8 *) (res + 1), ie_len, ie);
}