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
struct TYPE_3__ {char const* xre_format; unsigned int xre_num_fields; int xre_hits; int /*<<< orphan*/ * xre_fields; struct TYPE_3__* xre_next; } ;
typedef  TYPE_1__ xo_retain_entry_t ;
typedef  int /*<<< orphan*/  xo_field_info_t ;
struct TYPE_4__ {TYPE_1__** xr_bucket; } ;

/* Variables and functions */
 TYPE_2__ xo_retain ; 
 scalar_t__ xo_retain_count ; 
 unsigned int xo_retain_hash (char const*) ; 

__attribute__((used)) static int
xo_retain_find (const char *fmt, xo_field_info_t **valp, unsigned *nump)
{
    if (xo_retain_count == 0)
	return -1;

    unsigned hash = xo_retain_hash(fmt);
    xo_retain_entry_t *xrep;

    for (xrep = xo_retain.xr_bucket[hash]; xrep != NULL;
	 xrep = xrep->xre_next) {
	if (xrep->xre_format == fmt) {
	    *valp = xrep->xre_fields;
	    *nump = xrep->xre_num_fields;
	    xrep->xre_hits += 1;
	    return 0;
	}
    }

    return -1;
}