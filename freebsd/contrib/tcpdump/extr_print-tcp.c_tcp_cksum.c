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
typedef  int /*<<< orphan*/  u_int ;
struct tcphdr {int dummy; } ;
struct ip {int dummy; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int nextproto4_cksum (int /*<<< orphan*/ *,struct ip const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tcp_cksum(netdissect_options *ndo,
          register const struct ip *ip,
          register const struct tcphdr *tp,
          register u_int len)
{
	return nextproto4_cksum(ndo, ip, (const uint8_t *)tp, len, len,
				IPPROTO_TCP);
}