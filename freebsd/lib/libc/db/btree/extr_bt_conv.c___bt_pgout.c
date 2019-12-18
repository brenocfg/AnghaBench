#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int u_char ;
typedef  scalar_t__ pgno_t ;
typedef  size_t indx_t ;
struct TYPE_5__ {int flags; int pgno; int prevpg; int nextpg; int /*<<< orphan*/  upper; int /*<<< orphan*/  lower; int /*<<< orphan*/ * linp; } ;
typedef  TYPE_1__ PAGE ;
typedef  int /*<<< orphan*/  BTREE ;

/* Variables and functions */
 int /*<<< orphan*/  B_NEEDSWAP ; 
 int /*<<< orphan*/  F_ISSET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ GETBINTERNAL (TYPE_1__*,size_t) ; 
 scalar_t__ GETBLEAF (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  M_16_SWAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_32_SWAP (int) ; 
 size_t NEXTINDEX (TYPE_1__*) ; 
 int /*<<< orphan*/  P_32_SWAP (char*) ; 
 int P_BIGDATA ; 
 int P_BIGKEY ; 
 int P_BINTERNAL ; 
 int P_BLEAF ; 
 scalar_t__ P_META ; 
 int P_TYPE ; 
 int /*<<< orphan*/  mswap (void*) ; 

void
__bt_pgout(void *t, pgno_t pg, void *pp)
{
	PAGE *h;
	indx_t i, top;
	u_char flags;
	char *p;

	if (!F_ISSET(((BTREE *)t), B_NEEDSWAP))
		return;
	if (pg == P_META) {
		mswap(pp);
		return;
	}

	h = pp;
	top = NEXTINDEX(h);
	if ((h->flags & P_TYPE) == P_BINTERNAL)
		for (i = 0; i < top; i++) {
			p = (char *)GETBINTERNAL(h, i);
			P_32_SWAP(p);
			p += sizeof(u_int32_t);
			P_32_SWAP(p);
			p += sizeof(pgno_t);
			if (*(u_char *)p & P_BIGKEY) {
				p += sizeof(u_char);
				P_32_SWAP(p);
				p += sizeof(pgno_t);
				P_32_SWAP(p);
			}
			M_16_SWAP(h->linp[i]);
		}
	else if ((h->flags & P_TYPE) == P_BLEAF)
		for (i = 0; i < top; i++) {
			p = (char *)GETBLEAF(h, i);
			P_32_SWAP(p);
			p += sizeof(u_int32_t);
			P_32_SWAP(p);
			p += sizeof(u_int32_t);
			flags = *(u_char *)p;
			if (flags & (P_BIGKEY | P_BIGDATA)) {
				p += sizeof(u_char);
				if (flags & P_BIGKEY) {
					P_32_SWAP(p);
					p += sizeof(pgno_t);
					P_32_SWAP(p);
				}
				if (flags & P_BIGDATA) {
					p += sizeof(u_int32_t);
					P_32_SWAP(p);
					p += sizeof(pgno_t);
					P_32_SWAP(p);
				}
			}
			M_16_SWAP(h->linp[i]);
		}

	M_32_SWAP(h->pgno);
	M_32_SWAP(h->prevpg);
	M_32_SWAP(h->nextpg);
	M_32_SWAP(h->flags);
	M_16_SWAP(h->lower);
	M_16_SWAP(h->upper);
}