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
typedef  scalar_t__ uint16_t ;
struct nm_iphdr {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; scalar_t__ protocol; } ;

/* Variables and functions */
 int /*<<< orphan*/  htobe16 (scalar_t__) ; 
 scalar_t__ in_pseudo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nm_os_csum_fold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nm_os_csum_raw (void*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nm_prerr (char*) ; 

void
nm_os_csum_tcpudp_ipv4(struct nm_iphdr *iph, void *data,
					size_t datalen, uint16_t *check)
{
#ifdef INET
	uint16_t pseudolen = datalen + iph->protocol;

	/* Compute and insert the pseudo-header cheksum. */
	*check = in_pseudo(iph->saddr, iph->daddr,
				 htobe16(pseudolen));
	/* Compute the checksum on TCP/UDP header + payload
	 * (includes the pseudo-header).
	 */
	*check = nm_os_csum_fold(nm_os_csum_raw(data, datalen, 0));
#else
	static int notsupported = 0;
	if (!notsupported) {
		notsupported = 1;
		nm_prerr("inet4 segmentation not supported");
	}
#endif
}