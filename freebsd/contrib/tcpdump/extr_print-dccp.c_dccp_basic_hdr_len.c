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
struct dccp_hdr_ext {int dummy; } ;
struct dccp_hdr {int dummy; } ;

/* Variables and functions */
 scalar_t__ DCCPH_X (struct dccp_hdr const*) ; 

__attribute__((used)) static inline unsigned int dccp_basic_hdr_len(const struct dccp_hdr *dh)
{
	return DCCPH_X(dh) ? sizeof(struct dccp_hdr_ext) : sizeof(struct dccp_hdr);
}