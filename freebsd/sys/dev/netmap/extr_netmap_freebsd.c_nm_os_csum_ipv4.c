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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct nm_iphdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  in_cksum_hdr (void*) ; 
 int /*<<< orphan*/  nm_os_csum_fold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nm_os_csum_raw (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

uint16_t nm_os_csum_ipv4(struct nm_iphdr *iph)
{
#if 0
	return in_cksum_hdr((void *)iph);
#else
	return nm_os_csum_fold(nm_os_csum_raw((uint8_t*)iph, sizeof(struct nm_iphdr), 0));
#endif
}