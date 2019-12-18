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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct i40e_rx_ptype_decoded {scalar_t__ outer_ip; scalar_t__ outer_ip_ver; } ;
typedef  TYPE_1__* if_rxd_info_t ;
struct TYPE_3__ {int /*<<< orphan*/  iri_csum_data; int /*<<< orphan*/  iri_csum_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSUM_L3_CALC ; 
 int /*<<< orphan*/  CSUM_L3_VALID ; 
 int /*<<< orphan*/  CSUM_L4_CALC ; 
 int /*<<< orphan*/  CSUM_L4_VALID ; 
 int I40E_RX_DESC_ERROR_IPE_SHIFT ; 
 int I40E_RX_DESC_ERROR_L4E_SHIFT ; 
 int I40E_RX_DESC_STATUS_IPV6EXADD_SHIFT ; 
 int I40E_RX_DESC_STATUS_L3L4P_SHIFT ; 
 scalar_t__ I40E_RX_PTYPE_OUTER_IP ; 
 scalar_t__ I40E_RX_PTYPE_OUTER_IPV6 ; 
 struct i40e_rx_ptype_decoded decode_rx_desc_ptype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int) ; 

__attribute__((used)) static void
ixl_rx_checksum(if_rxd_info_t ri, u32 status, u32 error, u8 ptype)
{
	struct i40e_rx_ptype_decoded decoded;

	ri->iri_csum_flags = 0;

	/* No L3 or L4 checksum was calculated */
	if (!(status & (1 << I40E_RX_DESC_STATUS_L3L4P_SHIFT)))
		return;

	decoded = decode_rx_desc_ptype(ptype);

	/* IPv6 with extension headers likely have bad csum */
	if (decoded.outer_ip == I40E_RX_PTYPE_OUTER_IP &&
	    decoded.outer_ip_ver == I40E_RX_PTYPE_OUTER_IPV6) {
		if (status &
		    (1 << I40E_RX_DESC_STATUS_IPV6EXADD_SHIFT)) {
			ri->iri_csum_flags = 0;
			return;
		}
	}

	ri->iri_csum_flags |= CSUM_L3_CALC;

	/* IPv4 checksum error */
	if (error & (1 << I40E_RX_DESC_ERROR_IPE_SHIFT))
		return;

	ri->iri_csum_flags |= CSUM_L3_VALID;
	ri->iri_csum_flags |= CSUM_L4_CALC;

	/* L4 checksum error */
	if (error & (1 << I40E_RX_DESC_ERROR_L4E_SHIFT))
		return;

	ri->iri_csum_flags |= CSUM_L4_VALID;
	ri->iri_csum_data |= htons(0xffff);
}