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

/* Variables and functions */
 int /*<<< orphan*/  nlm_write_ucore_csuminfo (unsigned int) ; 

__attribute__((used)) static __inline__ void
nlm_ucore_csum_setup(int iphdr_start, int iphdr_len)
{
	unsigned int val = 0;

	val |= ((iphdr_len & 0xff) << 8);
	val |= (iphdr_len & 0xff);
	nlm_write_ucore_csuminfo(val);
}