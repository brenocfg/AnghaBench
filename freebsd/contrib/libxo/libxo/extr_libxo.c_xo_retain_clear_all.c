#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* xre_next; } ;
typedef  TYPE_1__ xo_retain_entry_t ;
struct TYPE_5__ {TYPE_1__** xr_bucket; } ;

/* Variables and functions */
 int RETAIN_HASH_SIZE ; 
 int /*<<< orphan*/  xo_free (TYPE_1__*) ; 
 TYPE_2__ xo_retain ; 
 scalar_t__ xo_retain_count ; 

void
xo_retain_clear_all (void)
{
    int i;
    xo_retain_entry_t *xrep, *next;

    for (i = 0; i < RETAIN_HASH_SIZE; i++) {
	for (xrep = xo_retain.xr_bucket[i]; xrep; xrep = next) {
	    next = xrep->xre_next;
	    xo_free(xrep);
	}
	xo_retain.xr_bucket[i] = NULL;
    }
    xo_retain_count = 0;
}