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
struct bgscan_learn_bss {int num_neigh; int /*<<< orphan*/ * neigh; int /*<<< orphan*/  bssid; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 scalar_t__ bssid_in_array (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*) ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/ * os_realloc_array (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void bgscan_learn_add_neighbor(struct bgscan_learn_bss *bss,
				      const u8 *bssid)
{
	u8 *n;

	if (os_memcmp(bss->bssid, bssid, ETH_ALEN) == 0)
		return;
	if (bssid_in_array(bss->neigh, bss->num_neigh, bssid))
		return;

	n = os_realloc_array(bss->neigh, bss->num_neigh + 1, ETH_ALEN);
	if (n == NULL)
		return;

	os_memcpy(n + bss->num_neigh * ETH_ALEN, bssid, ETH_ALEN);
	bss->neigh = n;
	bss->num_neigh++;
}