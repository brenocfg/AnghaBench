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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int /*<<< orphan*/  u_int16_t ;
struct ip6_hdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REDUCE ; 
 int _in6_cksum_pseudo (struct ip6_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
in6_cksum_pseudo(struct ip6_hdr *ip6, uint32_t len, uint8_t nxt, uint16_t csum)
{
	int sum;
	union {
		u_int16_t s[2];
		u_int32_t l;
	} l_util;

	sum = _in6_cksum_pseudo(ip6, len, nxt, csum);
	REDUCE;
	return (sum);
}