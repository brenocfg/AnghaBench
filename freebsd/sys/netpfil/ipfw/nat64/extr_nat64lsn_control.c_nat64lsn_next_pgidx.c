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
union nat64lsn_pgidx {int chunk; int port; int proto; scalar_t__ addr; int /*<<< orphan*/  index; } ;
struct nat64lsn_pg {int chunks_count; } ;
struct nat64lsn_cfg {scalar_t__ pmask4; } ;

/* Variables and functions */
#define  IPPROTO_ICMP 129 
#define  IPPROTO_TCP 128 
 int IPPROTO_UDP ; 
 int /*<<< orphan*/  LAST_IDX ; 
 int NAT64_MIN_PORT ; 
 int UINT16_MAX ; 

__attribute__((used)) static int
nat64lsn_next_pgidx(struct nat64lsn_cfg *cfg, struct nat64lsn_pg *pg,
    union nat64lsn_pgidx *idx)
{

	/* First iterate over chunks */
	if (pg != NULL) {
		if (idx->chunk < pg->chunks_count - 1) {
			idx->chunk++;
			return (0);
		}
	}
	idx->chunk = 0;
	/* Then over PGs */
	if (idx->port < UINT16_MAX - 64) {
		idx->port += 64;
		return (0);
	}
	idx->port = NAT64_MIN_PORT;
	/* Then over supported protocols */
	switch (idx->proto) {
	case IPPROTO_ICMP:
		idx->proto = IPPROTO_TCP;
		return (0);
	case IPPROTO_TCP:
		idx->proto = IPPROTO_UDP;
		return (0);
	default:
		idx->proto = IPPROTO_ICMP;
	}
	/* And then over IPv4 alias addresses */
	if (idx->addr < cfg->pmask4) {
		idx->addr++;
		return (1);	/* New states group is needed */
	}
	idx->index = LAST_IDX;
	return (-1);		/* No more states */
}