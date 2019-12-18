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
struct ibss_rsn_peer {int /*<<< orphan*/  addr; struct ibss_rsn_peer* next; } ;
struct ibss_rsn {struct ibss_rsn_peer* peers; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ibss_rsn_peer * ibss_rsn_get_peer(struct ibss_rsn *ibss_rsn,
						const u8 *addr)
{
	struct ibss_rsn_peer *peer;

	for (peer = ibss_rsn->peers; peer; peer = peer->next)
		if (os_memcmp(addr, peer->addr, ETH_ALEN) == 0)
			break;
	return peer;
}