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

/* Variables and functions */
 int ETH_ALEN ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void joint_two_mac(const u8 *mac1, const u8 *mac2, u8 *out)
{
	if (os_memcmp(mac1, mac2, ETH_ALEN) < 0) {
		os_memcpy(out, mac1, ETH_ALEN);
		os_memcpy(out + ETH_ALEN, mac2, ETH_ALEN);
	} else {
		os_memcpy(out, mac2, ETH_ALEN);
		os_memcpy(out + ETH_ALEN, mac1, ETH_ALEN);
	}
}