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
struct sockaddr_storage {int dummy; } ;
struct delegpt_ns {int got6; int got4; int resolved; } ;
struct delegpt {int /*<<< orphan*/  dp_type_mlc; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 scalar_t__ addr_is_ip6 (struct sockaddr_storage*,int /*<<< orphan*/ ) ; 
 int delegpt_add_addr_mlc (struct delegpt*,struct sockaddr_storage*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct delegpt_ns* delegpt_find_ns (struct delegpt*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  log_assert (int /*<<< orphan*/ ) ; 

int delegpt_add_target_mlc(struct delegpt* dp, uint8_t* name, size_t namelen,
	struct sockaddr_storage* addr, socklen_t addrlen, uint8_t bogus,
	uint8_t lame)
{
	struct delegpt_ns* ns = delegpt_find_ns(dp, name, namelen);
	log_assert(dp->dp_type_mlc);
	if(!ns) {
		/* ignore it */
		return 1;
	}
	if(!lame) {
		if(addr_is_ip6(addr, addrlen))
			ns->got6 = 1;
		else	ns->got4 = 1;
		if(ns->got4 && ns->got6)
			ns->resolved = 1;
	}
	return delegpt_add_addr_mlc(dp, addr, addrlen, bogus, lame, NULL);
}