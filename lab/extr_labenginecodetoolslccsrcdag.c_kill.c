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
struct TYPE_4__ {TYPE_1__** kids; int /*<<< orphan*/  op; } ;
struct dag {struct dag* hlink; TYPE_2__ node; } ;
struct TYPE_3__ {scalar_t__* syms; int /*<<< orphan*/  op; } ;
typedef  scalar_t__ Symbol ;

/* Variables and functions */
 scalar_t__ INDIR ; 
 int NELEMS (struct dag**) ; 
 struct dag** buckets ; 
 scalar_t__ generic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isaddrop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nodecount ; 

__attribute__((used)) static void kill(Symbol p) {
	int i;
	struct dag **q;

	for (i = 0; i < NELEMS(buckets); i++)
		for (q = &buckets[i]; *q; )
			if (generic((*q)->node.op) == INDIR &&
			    (!isaddrop((*q)->node.kids[0]->op)
			     || (*q)->node.kids[0]->syms[0] == p)) {
				*q = (*q)->hlink;
				--nodecount;
			} else
				q = &(*q)->hlink;
}