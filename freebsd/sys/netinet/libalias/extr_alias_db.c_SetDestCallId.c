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
typedef  int /*<<< orphan*/  u_int16_t ;
struct libalias {int deleteAllLinks; } ;
struct alias_link {int /*<<< orphan*/  link_type; int /*<<< orphan*/  alias_port; int /*<<< orphan*/  src_port; int /*<<< orphan*/  alias_addr; int /*<<< orphan*/  dst_addr; int /*<<< orphan*/  src_addr; struct libalias* la; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIBALIAS_LOCK_ASSERT (struct libalias*) ; 
 int /*<<< orphan*/  ReLink (struct alias_link*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
SetDestCallId(struct alias_link *lnk, u_int16_t cid)
{
	struct libalias *la = lnk->la;

	LIBALIAS_LOCK_ASSERT(la);
	la->deleteAllLinks = 1;
	ReLink(lnk, lnk->src_addr, lnk->dst_addr, lnk->alias_addr,
	    lnk->src_port, cid, lnk->alias_port, lnk->link_type);
	la->deleteAllLinks = 0;
}