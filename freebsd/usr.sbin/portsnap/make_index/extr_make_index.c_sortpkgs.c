#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * p; } ;
typedef  int /*<<< orphan*/  PORT ;
typedef  TYPE_1__ DEP ;

/* Variables and functions */
 int /*<<< orphan*/  heapifypkgs (TYPE_1__*,size_t,size_t) ; 

__attribute__((used)) static void
sortpkgs(DEP * d, size_t nd)
{
	size_t i;
	PORT * tmp;

	if (nd == 0)
		return;

	for (i = nd; i > 0; i--)
		heapifypkgs(d, nd, i - 1);	/* Build a heap */
	for (i = nd - 1; i > 0; i--) {
		tmp = d[0].p;			/* Extract elements */
		d[0].p = d[i].p;
		d[i].p = tmp;
		heapifypkgs(d, i, 0);		/* And re-heapify */
	}
}