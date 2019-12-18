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
struct hnamemem {int addr; struct hnamemem* nxt; int /*<<< orphan*/ * name; } ;
typedef  int /*<<< orphan*/  netdissect_options ;
struct TYPE_2__ {int /*<<< orphan*/  v; int /*<<< orphan*/ * s; } ;

/* Variables and functions */
 int HASHNAMESIZE ; 
 int htons (int /*<<< orphan*/ ) ; 
 TYPE_1__* ipxsap_db ; 
 struct hnamemem* ipxsaptable ; 
 struct hnamemem* newhnamemem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
init_ipxsaparray(netdissect_options *ndo)
{
	register int i;
	register struct hnamemem *table;

	for (i = 0; ipxsap_db[i].s != NULL; i++) {
		int j = htons(ipxsap_db[i].v) & (HASHNAMESIZE-1);
		table = &ipxsaptable[j];
		while (table->name)
			table = table->nxt;
		table->name = ipxsap_db[i].s;
		table->addr = htons(ipxsap_db[i].v);
		table->nxt = newhnamemem(ndo);
	}
}