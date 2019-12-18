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
struct cfg_s {int flows; int /*<<< orphan*/  loops; } ;
struct TYPE_3__ {scalar_t__ tot_bytes; } ;
struct TYPE_4__ {TYPE_1__ ni; } ;

/* Variables and functions */
 int /*<<< orphan*/  DX (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ND (int,char*,int,unsigned long long) ; 
 TYPE_2__* q ; 

int
dump(struct cfg_s *c)
{
	int i;

	for (i=0; i < c->flows; i++) {
		//struct dn_queue *q = FI2Q(c, i);
		ND(1, "queue %4d tot %10llu", i,
		    (unsigned long long)q->ni.tot_bytes);
	}
	DX(1, "done %d loops\n", c->loops);
	return 0;
}