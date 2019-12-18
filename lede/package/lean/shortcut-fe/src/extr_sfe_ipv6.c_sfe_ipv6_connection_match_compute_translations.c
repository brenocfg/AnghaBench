#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  void* u16 ;
struct sfe_ipv6_connection_match {int flags; void* xlate_dest_csum_adjustment; TYPE_4__* xlate_dest_ip; int /*<<< orphan*/  xlate_dest_port; int /*<<< orphan*/  match_dest_port; TYPE_3__* match_dest_ip; void* xlate_src_csum_adjustment; TYPE_2__* xlate_src_ip; int /*<<< orphan*/  xlate_src_port; int /*<<< orphan*/  match_src_port; TYPE_1__* match_src_ip; } ;
struct TYPE_8__ {int /*<<< orphan*/ * addr; } ;
struct TYPE_7__ {int /*<<< orphan*/ * addr; } ;
struct TYPE_6__ {int /*<<< orphan*/ * addr; } ;
struct TYPE_5__ {int /*<<< orphan*/ * addr; } ;

/* Variables and functions */
 int SFE_IPV6_CONNECTION_MATCH_FLAG_XLATE_DEST ; 
 int SFE_IPV6_CONNECTION_MATCH_FLAG_XLATE_SRC ; 

__attribute__((used)) static void sfe_ipv6_connection_match_compute_translations(struct sfe_ipv6_connection_match *cm)
{
	u32 diff[9];
	u32 *idx_32;
	u16 *idx_16;

	/*
	 * Before we insert the entry look to see if this is tagged as doing address
	 * translations.  If it is then work out the adjustment that we need to apply
	 * to the transport checksum.
	 */
	if (cm->flags & SFE_IPV6_CONNECTION_MATCH_FLAG_XLATE_SRC) {
		u32 adj = 0;
		u32 carry = 0;

		/*
		 * Precompute an incremental checksum adjustment so we can
		 * edit packets in this stream very quickly.  The algorithm is from RFC1624.
		 */
		idx_32 = diff;
		*(idx_32++) = cm->match_src_ip->addr[0];
		*(idx_32++) = cm->match_src_ip->addr[1];
		*(idx_32++) = cm->match_src_ip->addr[2];
		*(idx_32++) = cm->match_src_ip->addr[3];

		idx_16 = (u16 *)idx_32;
		*(idx_16++) = cm->match_src_port;
		*(idx_16++) = ~cm->xlate_src_port;
		idx_32 = (u32 *)idx_16;

		*(idx_32++) = ~cm->xlate_src_ip->addr[0];
		*(idx_32++) = ~cm->xlate_src_ip->addr[1];
		*(idx_32++) = ~cm->xlate_src_ip->addr[2];
		*(idx_32++) = ~cm->xlate_src_ip->addr[3];

		/*
		 * When we compute this fold it down to a 16-bit offset
		 * as that way we can avoid having to do a double
		 * folding of the twos-complement result because the
		 * addition of 2 16-bit values cannot cause a double
		 * wrap-around!
		 */
		for (idx_32 = diff; idx_32 < diff + 9; idx_32++) {
			u32 w = *idx_32;
			adj += carry;
			adj += w;
			carry = (w > adj);
		}
		adj += carry;
		adj = (adj & 0xffff) + (adj >> 16);
		adj = (adj & 0xffff) + (adj >> 16);
		cm->xlate_src_csum_adjustment = (u16)adj;
	}

	if (cm->flags & SFE_IPV6_CONNECTION_MATCH_FLAG_XLATE_DEST) {
		u32 adj = 0;
		u32 carry = 0;

		/*
		 * Precompute an incremental checksum adjustment so we can
		 * edit packets in this stream very quickly.  The algorithm is from RFC1624.
		 */
		idx_32 = diff;
		*(idx_32++) = cm->match_dest_ip->addr[0];
		*(idx_32++) = cm->match_dest_ip->addr[1];
		*(idx_32++) = cm->match_dest_ip->addr[2];
		*(idx_32++) = cm->match_dest_ip->addr[3];

		idx_16 = (u16 *)idx_32;
		*(idx_16++) = cm->match_dest_port;
		*(idx_16++) = ~cm->xlate_dest_port;
		idx_32 = (u32 *)idx_16;

		*(idx_32++) = ~cm->xlate_dest_ip->addr[0];
		*(idx_32++) = ~cm->xlate_dest_ip->addr[1];
		*(idx_32++) = ~cm->xlate_dest_ip->addr[2];
		*(idx_32++) = ~cm->xlate_dest_ip->addr[3];

		/*
		 * When we compute this fold it down to a 16-bit offset
		 * as that way we can avoid having to do a double
		 * folding of the twos-complement result because the
		 * addition of 2 16-bit values cannot cause a double
		 * wrap-around!
		 */
		for (idx_32 = diff; idx_32 < diff + 9; idx_32++) {
			u32 w = *idx_32;
			adj += carry;
			adj += w;
			carry = (w > adj);
		}
		adj += carry;
		adj = (adj & 0xffff) + (adj >> 16);
		adj = (adj & 0xffff) + (adj >> 16);
		cm->xlate_dest_csum_adjustment = (u16)adj;
	}
}