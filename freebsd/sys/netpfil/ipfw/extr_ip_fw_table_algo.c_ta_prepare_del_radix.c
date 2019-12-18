#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tentry_info {int masklen; scalar_t__ subtype; } ;
struct TYPE_5__ {int /*<<< orphan*/  ma; int /*<<< orphan*/  sa; } ;
struct TYPE_4__ {int /*<<< orphan*/  ma; int /*<<< orphan*/  sa; } ;
struct TYPE_6__ {TYPE_2__ a6; TYPE_1__ a4; } ;
struct ta_buf_radix {struct sockaddr* mask_ptr; struct sockaddr* addr_ptr; TYPE_3__ addr; } ;
struct sockaddr {int dummy; } ;
struct ip_fw_chain {int dummy; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int EINVAL ; 
 int /*<<< orphan*/  tei_to_sockaddr_ent (struct tentry_info*,struct sockaddr*,struct sockaddr*,int*) ; 

__attribute__((used)) static int
ta_prepare_del_radix(struct ip_fw_chain *ch, struct tentry_info *tei,
    void *ta_buf)
{
	struct ta_buf_radix *tb;
	struct sockaddr *addr, *mask;
	int mlen, set_mask;

	tb = (struct ta_buf_radix *)ta_buf;

	mlen = tei->masklen;
	set_mask = 0;

	if (tei->subtype == AF_INET) {
		if (mlen > 32)
			return (EINVAL);

		addr = (struct sockaddr *)&tb->addr.a4.sa;
		mask = (struct sockaddr *)&tb->addr.a4.ma;
#ifdef INET6
	} else if (tei->subtype == AF_INET6) {
		if (mlen > 128)
			return (EINVAL);

		addr = (struct sockaddr *)&tb->addr.a6.sa;
		mask = (struct sockaddr *)&tb->addr.a6.ma;
#endif
	} else
		return (EINVAL);

	tei_to_sockaddr_ent(tei, addr, mask, &set_mask);
	tb->addr_ptr = addr;
	if (set_mask != 0)
		tb->mask_ptr = mask;

	return (0);
}