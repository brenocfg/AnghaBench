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
typedef  int u16 ;
struct sfe_ipv6_ip_hdr {int dummy; } ;
typedef  int __be16 ;

/* Variables and functions */
 int SFE_IPV6_DSCP_MASK ; 
 int htons (int) ; 

__attribute__((used)) static inline void sfe_ipv6_change_dsfield(struct sfe_ipv6_ip_hdr *iph, u8 dscp)
{
	__be16 *p = (__be16 *)iph;

	*p = ((*p & htons(SFE_IPV6_DSCP_MASK)) | htons((u16)dscp << 4));
}