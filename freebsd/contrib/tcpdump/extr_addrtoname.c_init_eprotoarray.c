#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hnamemem {int addr; struct hnamemem* nxt; scalar_t__ name; } ;
typedef  int /*<<< orphan*/  netdissect_options ;
struct TYPE_2__ {int /*<<< orphan*/  p; scalar_t__ s; } ;

/* Variables and functions */
 int HASHNAMESIZE ; 
 TYPE_1__* eproto_db ; 
 struct hnamemem* eprototable ; 
 int htons (int /*<<< orphan*/ ) ; 
 struct hnamemem* newhnamemem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
init_eprotoarray(netdissect_options *ndo)
{
	register int i;
	register struct hnamemem *table;

	for (i = 0; eproto_db[i].s; i++) {
		int j = htons(eproto_db[i].p) & (HASHNAMESIZE-1);
		table = &eprototable[j];
		while (table->name)
			table = table->nxt;
		table->name = eproto_db[i].s;
		table->addr = htons(eproto_db[i].p);
		table->nxt = newhnamemem(ndo);
	}
}