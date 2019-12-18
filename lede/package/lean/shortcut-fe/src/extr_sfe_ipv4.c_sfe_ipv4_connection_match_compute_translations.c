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
typedef  int u32 ;
typedef  int u16 ;
struct sfe_ipv4_connection_match {int flags; int match_src_ip; int xlate_src_ip; int xlate_src_port; int match_src_port; int xlate_src_csum_adjustment; int match_dest_ip; int xlate_dest_ip; int xlate_dest_port; int match_dest_port; int xlate_dest_csum_adjustment; int xlate_src_partial_csum_adjustment; int xlate_dest_partial_csum_adjustment; } ;

/* Variables and functions */
 int SFE_IPV4_CONNECTION_MATCH_FLAG_XLATE_DEST ; 
 int SFE_IPV4_CONNECTION_MATCH_FLAG_XLATE_SRC ; 

__attribute__((used)) static void sfe_ipv4_connection_match_compute_translations(struct sfe_ipv4_connection_match *cm)
{
	/*
	 * Before we insert the entry look to see if this is tagged as doing address
	 * translations.  If it is then work out the adjustment that we need to apply
	 * to the transport checksum.
	 */
	if (cm->flags & SFE_IPV4_CONNECTION_MATCH_FLAG_XLATE_SRC) {
		/*
		 * Precompute an incremental checksum adjustment so we can
		 * edit packets in this stream very quickly.  The algorithm is from RFC1624.
		 */
		u16 src_ip_hi = cm->match_src_ip >> 16;
		u16 src_ip_lo = cm->match_src_ip & 0xffff;
		u32 xlate_src_ip = ~cm->xlate_src_ip;
		u16 xlate_src_ip_hi = xlate_src_ip >> 16;
		u16 xlate_src_ip_lo = xlate_src_ip & 0xffff;
		u16 xlate_src_port = ~cm->xlate_src_port;
		u32 adj;

		/*
		 * When we compute this fold it down to a 16-bit offset
		 * as that way we can avoid having to do a double
		 * folding of the twos-complement result because the
		 * addition of 2 16-bit values cannot cause a double
		 * wrap-around!
		 */
		adj = src_ip_hi + src_ip_lo + cm->match_src_port
		      + xlate_src_ip_hi + xlate_src_ip_lo + xlate_src_port;
		adj = (adj & 0xffff) + (adj >> 16);
		adj = (adj & 0xffff) + (adj >> 16);
		cm->xlate_src_csum_adjustment = (u16)adj;

	}

	if (cm->flags & SFE_IPV4_CONNECTION_MATCH_FLAG_XLATE_DEST) {
		/*
		 * Precompute an incremental checksum adjustment so we can
		 * edit packets in this stream very quickly.  The algorithm is from RFC1624.
		 */
		u16 dest_ip_hi = cm->match_dest_ip >> 16;
		u16 dest_ip_lo = cm->match_dest_ip & 0xffff;
		u32 xlate_dest_ip = ~cm->xlate_dest_ip;
		u16 xlate_dest_ip_hi = xlate_dest_ip >> 16;
		u16 xlate_dest_ip_lo = xlate_dest_ip & 0xffff;
		u16 xlate_dest_port = ~cm->xlate_dest_port;
		u32 adj;

		/*
		 * When we compute this fold it down to a 16-bit offset
		 * as that way we can avoid having to do a double
		 * folding of the twos-complement result because the
		 * addition of 2 16-bit values cannot cause a double
		 * wrap-around!
		 */
		adj = dest_ip_hi + dest_ip_lo + cm->match_dest_port
		      + xlate_dest_ip_hi + xlate_dest_ip_lo + xlate_dest_port;
		adj = (adj & 0xffff) + (adj >> 16);
		adj = (adj & 0xffff) + (adj >> 16);
		cm->xlate_dest_csum_adjustment = (u16)adj;
	}

	if (cm->flags & SFE_IPV4_CONNECTION_MATCH_FLAG_XLATE_SRC) {
		u32 adj = ~cm->match_src_ip + cm->xlate_src_ip;
		if (adj < cm->xlate_src_ip) {
			adj++;
		}

		adj = (adj & 0xffff) + (adj >> 16);
		adj = (adj & 0xffff) + (adj >> 16);
		cm->xlate_src_partial_csum_adjustment = (u16)adj;
	}

	if (cm->flags & SFE_IPV4_CONNECTION_MATCH_FLAG_XLATE_DEST) {
		u32 adj = ~cm->match_dest_ip + cm->xlate_dest_ip;
		if (adj < cm->xlate_dest_ip) {
			adj++;
		}

		adj = (adj & 0xffff) + (adj >> 16);
		adj = (adj & 0xffff) + (adj >> 16);
		cm->xlate_dest_partial_csum_adjustment = (u16)adj;
	}

}