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
typedef  int u64 ;
struct kvmppc_slb {int vsid; } ;
typedef  int gva_t ;

/* Variables and functions */
 int VPN_SHIFT ; 
 int kvmppc_slb_offset_mask (struct kvmppc_slb*) ; 
 int kvmppc_slb_sid_shift (struct kvmppc_slb*) ; 

__attribute__((used)) static u64 kvmppc_slb_calc_vpn(struct kvmppc_slb *slb, gva_t eaddr)
{
	eaddr &= kvmppc_slb_offset_mask(slb);

	return (eaddr >> VPN_SHIFT) |
		((slb->vsid) << (kvmppc_slb_sid_shift(slb) - VPN_SHIFT));
}