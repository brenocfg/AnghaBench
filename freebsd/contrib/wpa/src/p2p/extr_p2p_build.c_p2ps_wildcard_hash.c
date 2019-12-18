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
typedef  scalar_t__ u8 ;
struct p2p_data {int /*<<< orphan*/  wild_card_hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  P2PS_HASH_LEN ; 
 scalar_t__ os_memcmp (scalar_t__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int p2ps_wildcard_hash(struct p2p_data *p2p,
			      const u8 *hash, u8 hash_count)
{
	u8 i;
	const u8 *test = hash;

	for (i = 0; i < hash_count; i++) {
		if (os_memcmp(test, p2p->wild_card_hash, P2PS_HASH_LEN) == 0)
			return 1;
		test += P2PS_HASH_LEN;
	}

	return 0;
}