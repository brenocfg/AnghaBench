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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ uint16_t ;
typedef  void* u_int ;
typedef  void* u_char ;
struct ip {int /*<<< orphan*/  ip_dst; int /*<<< orphan*/  ip_src; } ;
struct cksum_vec {int len; int /*<<< orphan*/  const* ptr; } ;
typedef  int /*<<< orphan*/  ph ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int IP_HL (struct ip const*) ; 
 int /*<<< orphan*/  UNALIGNED_MEMCPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ htons (scalar_t__) ; 
 int in_cksum (struct cksum_vec*,int) ; 
 int /*<<< orphan*/  ip_finddst (int /*<<< orphan*/ *,struct ip const*) ; 

int
nextproto4_cksum(netdissect_options *ndo,
                 const struct ip *ip, const uint8_t *data,
                 u_int len, u_int covlen, u_int next_proto)
{
	struct phdr {
		uint32_t src;
		uint32_t dst;
		u_char mbz;
		u_char proto;
		uint16_t len;
	} ph;
	struct cksum_vec vec[2];

	/* pseudo-header.. */
	ph.len = htons((uint16_t)len);
	ph.mbz = 0;
	ph.proto = next_proto;
	UNALIGNED_MEMCPY(&ph.src, &ip->ip_src, sizeof(uint32_t));
	if (IP_HL(ip) == 5)
		UNALIGNED_MEMCPY(&ph.dst, &ip->ip_dst, sizeof(uint32_t));
	else
		ph.dst = ip_finddst(ndo, ip);

	vec[0].ptr = (const uint8_t *)(void *)&ph;
	vec[0].len = sizeof(ph);
	vec[1].ptr = data;
	vec[1].len = covlen;
	return (in_cksum(vec, 2));
}