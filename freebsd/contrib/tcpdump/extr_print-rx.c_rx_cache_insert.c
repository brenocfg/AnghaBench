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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u_char ;
struct rx_header {int /*<<< orphan*/  const serviceId; int /*<<< orphan*/  const callNumber; } ;
struct rx_cache_entry {int dport; void* opcode; void* serviceId; int /*<<< orphan*/  server; int /*<<< orphan*/  client; void* callnum; } ;
struct ip {int /*<<< orphan*/  ip_dst; int /*<<< orphan*/  ip_src; } ;
struct TYPE_3__ {int /*<<< orphan*/  const* ndo_snapend; } ;
typedef  TYPE_1__ netdissect_options ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 void* EXTRACT_32BITS (int /*<<< orphan*/  const*) ; 
 size_t RX_CACHE_SIZE ; 
 int /*<<< orphan*/  UNALIGNED_MEMCPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct rx_cache_entry* rx_cache ; 
 size_t rx_cache_next ; 

__attribute__((used)) static void
rx_cache_insert(netdissect_options *ndo,
                const u_char *bp, const struct ip *ip, int dport)
{
	struct rx_cache_entry *rxent;
	const struct rx_header *rxh = (const struct rx_header *) bp;

	if (ndo->ndo_snapend - bp + 1 <= (int)(sizeof(struct rx_header) + sizeof(int32_t)))
		return;

	rxent = &rx_cache[rx_cache_next];

	if (++rx_cache_next >= RX_CACHE_SIZE)
		rx_cache_next = 0;

	rxent->callnum = EXTRACT_32BITS(&rxh->callNumber);
	UNALIGNED_MEMCPY(&rxent->client, &ip->ip_src, sizeof(uint32_t));
	UNALIGNED_MEMCPY(&rxent->server, &ip->ip_dst, sizeof(uint32_t));
	rxent->dport = dport;
	rxent->serviceId = EXTRACT_32BITS(&rxh->serviceId);
	rxent->opcode = EXTRACT_32BITS(bp + sizeof(struct rx_header));
}