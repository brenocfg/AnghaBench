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
 size_t ETH_ALEN ; 
 scalar_t__ match_mac_mask (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int addr_in_list(const u8 *addr, const u8 *list, size_t num)
{
	size_t i;

	for (i = 0; i < num; i++) {
		const u8 *a = list + i * ETH_ALEN * 2;
		const u8 *m = a + ETH_ALEN;

		if (match_mac_mask(a, addr, m))
			return 1;
	}
	return 0;
}