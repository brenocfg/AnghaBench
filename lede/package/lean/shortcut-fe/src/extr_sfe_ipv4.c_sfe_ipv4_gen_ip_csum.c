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
struct sfe_ipv4_ip_hdr {scalar_t__ check; } ;

/* Variables and functions */

__attribute__((used)) static inline u16 sfe_ipv4_gen_ip_csum(struct sfe_ipv4_ip_hdr *iph)
{
	u32 sum;
	u16 *i = (u16 *)iph;

	iph->check = 0;

	/*
	 * Generate the sum.
	 */
	sum = i[0] + i[1] + i[2] + i[3] + i[4] + i[5] + i[6] + i[7] + i[8] + i[9];

	/*
	 * Fold it to ones-complement form.
	 */
	sum = (sum & 0xffff) + (sum >> 16);
	sum = (sum & 0xffff) + (sum >> 16);

	return (u16)sum ^ 0xffff;
}