#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct cookie_state {size_t pte_idx; unsigned long mte_base; scalar_t__ prev_cookie; int nc; TYPE_2__* cookies; TYPE_1__* page_table; } ;
struct TYPE_4__ {unsigned long cookie_size; scalar_t__ cookie_addr; } ;
struct TYPE_3__ {unsigned long mte; } ;

/* Variables and functions */
 unsigned long PAGE_SIZE ; 
 scalar_t__ make_cookie (size_t,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  pagesize_code () ; 

__attribute__((used)) static void fill_cookies(struct cookie_state *sp, unsigned long pa,
			 unsigned long off, unsigned long len)
{
	do {
		unsigned long tlen, new = pa + PAGE_SIZE;
		u64 this_cookie;

		sp->page_table[sp->pte_idx].mte = sp->mte_base | pa;

		tlen = PAGE_SIZE;
		if (off)
			tlen = PAGE_SIZE - off;
		if (tlen > len)
			tlen = len;

		this_cookie = make_cookie(sp->pte_idx,
					  pagesize_code(), off);

		off = 0;

		if (this_cookie == sp->prev_cookie) {
			sp->cookies[sp->nc - 1].cookie_size += tlen;
		} else {
			sp->cookies[sp->nc].cookie_addr = this_cookie;
			sp->cookies[sp->nc].cookie_size = tlen;
			sp->nc++;
		}
		sp->prev_cookie = this_cookie + tlen;

		sp->pte_idx++;

		len -= tlen;
		pa = new;
	} while (len > 0);
}