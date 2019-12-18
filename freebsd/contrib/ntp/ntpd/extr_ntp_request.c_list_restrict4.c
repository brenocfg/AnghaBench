#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct info_restrict {void* mflags; void* rflags; void* count; void* mask; scalar_t__ v6_flag; void* addr; } ;
struct TYPE_7__ {int /*<<< orphan*/  mask; int /*<<< orphan*/  addr; } ;
struct TYPE_8__ {TYPE_1__ v4; } ;
struct TYPE_9__ {int /*<<< orphan*/  mflags; int /*<<< orphan*/  rflags; int /*<<< orphan*/  count; TYPE_2__ u; struct TYPE_9__* link; } ;
typedef  TYPE_3__ restrict_u ;
typedef  int /*<<< orphan*/  RestrictStackT ;

/* Variables and functions */
 scalar_t__ client_v6_capable ; 
 int /*<<< orphan*/  flushRestrictionStack (int /*<<< orphan*/ **) ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 scalar_t__ more_pkt () ; 
 scalar_t__ popRestriction (int /*<<< orphan*/ **,TYPE_3__ const**) ; 
 int /*<<< orphan*/  pushRestriction (int /*<<< orphan*/ **,TYPE_3__ const*) ; 

__attribute__((used)) static void
list_restrict4(
	const restrict_u *	res,
	struct info_restrict **	ppir
	)
{
	RestrictStackT *	rpad;
	struct info_restrict *	pir;

	pir = *ppir;
	for (rpad = NULL; res; res = res->link)
		if (!pushRestriction(&rpad, res))
			break;
	
	while (pir && popRestriction(&rpad, &res)) {
		pir->addr = htonl(res->u.v4.addr);
		if (client_v6_capable) 
			pir->v6_flag = 0;
		pir->mask = htonl(res->u.v4.mask);
		pir->count = htonl(res->count);
		pir->rflags = htons(res->rflags);
		pir->mflags = htons(res->mflags);
		pir = (struct info_restrict *)more_pkt();
	}
	flushRestrictionStack(&rpad);
	*ppir = pir;
}