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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u_int ;
struct dccp_hdr {int dccph_doff; } ;

/* Variables and functions */
 int DCCPH_CSCOV (struct dccp_hdr const*) ; 

__attribute__((used)) static inline u_int dccp_csum_coverage(const struct dccp_hdr* dh, u_int len)
{
	u_int cov;

	if (DCCPH_CSCOV(dh) == 0)
		return len;
	cov = (dh->dccph_doff + DCCPH_CSCOV(dh) - 1) * sizeof(uint32_t);
	return (cov > len)? len : cov;
}