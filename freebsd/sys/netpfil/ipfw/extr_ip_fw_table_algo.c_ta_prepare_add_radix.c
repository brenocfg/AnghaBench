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
struct TYPE_5__ {int /*<<< orphan*/  ma; } ;
struct TYPE_4__ {int /*<<< orphan*/  ma; } ;
struct TYPE_6__ {TYPE_2__ a6; TYPE_1__ a4; } ;
struct ta_buf_radix {struct sockaddr* mask_ptr; struct sockaddr* addr_ptr; struct radix_addr_xentry* ent_ptr; TYPE_3__ addr; } ;
struct sockaddr {int dummy; } ;
struct radix_addr_xentry {int masklen; int /*<<< orphan*/  addr6; int /*<<< orphan*/  addr; } ;
struct radix_addr_entry {int masklen; int /*<<< orphan*/  addr6; int /*<<< orphan*/  addr; } ;
struct ip_fw_chain {int dummy; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int EINVAL ; 
 int /*<<< orphan*/  M_IPFW_TBL ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tei_to_sockaddr_ent (struct tentry_info*,struct sockaddr*,struct sockaddr*,int*) ; 

__attribute__((used)) static int
ta_prepare_add_radix(struct ip_fw_chain *ch, struct tentry_info *tei,
    void *ta_buf)
{
	struct ta_buf_radix *tb;
	struct radix_addr_entry *ent;
#ifdef INET6
	struct radix_addr_xentry *xent;
#endif
	struct sockaddr *addr, *mask;
	int mlen, set_mask;

	tb = (struct ta_buf_radix *)ta_buf;

	mlen = tei->masklen;
	set_mask = 0;
	
	if (tei->subtype == AF_INET) {
#ifdef INET
		if (mlen > 32)
			return (EINVAL);
		ent = malloc(sizeof(*ent), M_IPFW_TBL, M_WAITOK | M_ZERO);
		ent->masklen = mlen;

		addr = (struct sockaddr *)&ent->addr;
		mask = (struct sockaddr *)&tb->addr.a4.ma;
		tb->ent_ptr = ent;
#endif
#ifdef INET6
	} else if (tei->subtype == AF_INET6) {
		/* IPv6 case */
		if (mlen > 128)
			return (EINVAL);
		xent = malloc(sizeof(*xent), M_IPFW_TBL, M_WAITOK | M_ZERO);
		xent->masklen = mlen;

		addr = (struct sockaddr *)&xent->addr6;
		mask = (struct sockaddr *)&tb->addr.a6.ma;
		tb->ent_ptr = xent;
#endif
	} else {
		/* Unknown CIDR type */
		return (EINVAL);
	}

	tei_to_sockaddr_ent(tei, addr, mask, &set_mask);
	/* Set pointers */
	tb->addr_ptr = addr;
	if (set_mask != 0)
		tb->mask_ptr = mask;

	return (0);
}