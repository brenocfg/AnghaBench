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
struct wpa_bss {int /*<<< orphan*/  ie_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  const* get_ie (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

const u8 * wpa_bss_get_ie(const struct wpa_bss *bss, u8 ie)
{
	return get_ie((const u8 *) (bss + 1), bss->ie_len, ie);
}