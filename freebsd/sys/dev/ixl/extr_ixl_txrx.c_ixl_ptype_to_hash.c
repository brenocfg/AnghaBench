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
struct i40e_rx_ptype_decoded {scalar_t__ outer_ip; scalar_t__ outer_ip_ver; int inner_prot; int /*<<< orphan*/  known; } ;

/* Variables and functions */
#define  I40E_RX_PTYPE_INNER_PROT_TCP 129 
#define  I40E_RX_PTYPE_INNER_PROT_UDP 128 
 scalar_t__ I40E_RX_PTYPE_OUTER_IPV4 ; 
 scalar_t__ I40E_RX_PTYPE_OUTER_IPV6 ; 
 scalar_t__ I40E_RX_PTYPE_OUTER_L2 ; 
 int M_HASHTYPE_OPAQUE ; 
 int M_HASHTYPE_RSS_IPV4 ; 
 int M_HASHTYPE_RSS_IPV6 ; 
 int M_HASHTYPE_RSS_TCP_IPV4 ; 
 int M_HASHTYPE_RSS_TCP_IPV6 ; 
 int M_HASHTYPE_RSS_UDP_IPV4 ; 
 int M_HASHTYPE_RSS_UDP_IPV6 ; 
 struct i40e_rx_ptype_decoded decode_rx_desc_ptype (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
ixl_ptype_to_hash(u8 ptype)
{
        struct i40e_rx_ptype_decoded	decoded;

	decoded = decode_rx_desc_ptype(ptype);

	if (!decoded.known)
		return M_HASHTYPE_OPAQUE;

	if (decoded.outer_ip == I40E_RX_PTYPE_OUTER_L2)
		return M_HASHTYPE_OPAQUE;

	/* Note: anything that gets to this point is IP */
        if (decoded.outer_ip_ver == I40E_RX_PTYPE_OUTER_IPV6) {
		switch (decoded.inner_prot) {
		case I40E_RX_PTYPE_INNER_PROT_TCP:
			return M_HASHTYPE_RSS_TCP_IPV6;
		case I40E_RX_PTYPE_INNER_PROT_UDP:
			return M_HASHTYPE_RSS_UDP_IPV6;
		default:
			return M_HASHTYPE_RSS_IPV6;
		}
	}
        if (decoded.outer_ip_ver == I40E_RX_PTYPE_OUTER_IPV4) {
		switch (decoded.inner_prot) {
		case I40E_RX_PTYPE_INNER_PROT_TCP:
			return M_HASHTYPE_RSS_TCP_IPV4;
		case I40E_RX_PTYPE_INNER_PROT_UDP:
			return M_HASHTYPE_RSS_UDP_IPV4;
		default:
			return M_HASHTYPE_RSS_IPV4;
		}
	}
	/* We should never get here!! */
	return M_HASHTYPE_OPAQUE;
}