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
typedef  int /*<<< orphan*/  uint16_t ;
struct ip {int ip_v; int ip_hl; scalar_t__ ip_sum; } ;
struct ibv_grh {int /*<<< orphan*/  version_tclass_flow; } ;
typedef  int /*<<< orphan*/  ip4h_checked ;

/* Variables and functions */
 int /*<<< orphan*/  EPROTONOSUPPORT ; 
 int be32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ipv4_calc_hdr_csum (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (struct ip*,struct ip*,int) ; 

__attribute__((used)) static inline int get_grh_header_version(struct ibv_grh *grh)
{
	int ip6h_version = (be32toh(grh->version_tclass_flow) >> 28) & 0xf;
	struct ip *ip4h = (struct ip *)((void *)grh + 20);
	struct ip ip4h_checked;

	if (ip6h_version != 6) {
		if (ip4h->ip_v == 4)
			return 4;
		errno = EPROTONOSUPPORT;
		return -1;
	}
	/* version may be 6 or 4 */
	if (ip4h->ip_hl != 5) /* IPv4 header length must be 5 for RoCE v2. */
		return 6;
	/*
	* Verify checksum.
	* We can't write on scattered buffers so we have to copy to temp
	* buffer.
	*/
	memcpy(&ip4h_checked, ip4h, sizeof(ip4h_checked));
	/* Need to set the checksum field (check) to 0 before re-calculating
	 * the checksum.
	 */
	ip4h_checked.ip_sum = 0;
	ip4h_checked.ip_sum = ipv4_calc_hdr_csum((uint16_t *)&ip4h_checked, 10);
	/* if IPv4 header checksum is OK, believe it */
	if (ip4h->ip_sum == ip4h_checked.ip_sum)
		return 4;
	return 6;
}