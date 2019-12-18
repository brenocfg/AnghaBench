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
typedef  scalar_t__ uint16_t ;
struct local_rrset {struct local_rrset* next; TYPE_2__* rrset; } ;
struct local_data {struct local_rrset* rrsets; } ;
struct TYPE_3__ {int /*<<< orphan*/  type; } ;
struct TYPE_4__ {TYPE_1__ rk; } ;

/* Variables and functions */
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
del_local_rrset(struct local_data* d, uint16_t dtype)
{
	struct local_rrset* prev=NULL, *p=d->rrsets;
	while(p && ntohs(p->rrset->rk.type) != dtype) {
		prev = p;
		p = p->next;
	}
	if(!p) 
		return; /* rrset type not found */
	/* unlink it */
	if(prev) prev->next = p->next;
	else d->rrsets = p->next;
	/* no memory recycling for zone deletions ... */
}