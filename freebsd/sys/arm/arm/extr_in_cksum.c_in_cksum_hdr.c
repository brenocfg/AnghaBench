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
typedef  union q_util {int dummy; } q_util ;
typedef  union l_util {int dummy; } l_util ;
typedef  int u_int64_t ;
typedef  int u_int ;
struct ip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REDUCE16 ; 
 int do_cksum (struct ip const*,int) ; 

u_int in_cksum_hdr(const struct ip *ip)
{
	u_int64_t sum = do_cksum(ip, sizeof(struct ip));
	union q_util q_util;
    	union l_util l_util;
	REDUCE16;
	return (~sum & 0xffff);
}