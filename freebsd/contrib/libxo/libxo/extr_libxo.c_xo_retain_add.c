#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char const* xre_format; unsigned int xre_num_fields; struct TYPE_5__* xre_next; int /*<<< orphan*/ * xre_fields; } ;
typedef  TYPE_1__ xo_retain_entry_t ;
typedef  int /*<<< orphan*/  xo_field_info_t ;
typedef  int ssize_t ;
struct TYPE_6__ {TYPE_1__** xr_bucket; } ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 TYPE_1__* xo_realloc (int /*<<< orphan*/ *,int) ; 
 TYPE_2__ xo_retain ; 
 int xo_retain_count ; 
 unsigned int xo_retain_hash (char const*) ; 

__attribute__((used)) static void
xo_retain_add (const char *fmt, xo_field_info_t *fields, unsigned num_fields)
{
    unsigned hash = xo_retain_hash(fmt);
    xo_retain_entry_t *xrep;
    ssize_t sz = sizeof(*xrep) + (num_fields + 1) * sizeof(*fields);
    xo_field_info_t *xfip;

    xrep = xo_realloc(NULL, sz);
    if (xrep == NULL)
	return;

    xfip = (xo_field_info_t *) &xrep[1];
    memcpy(xfip, fields, num_fields * sizeof(*fields));

    bzero(xrep, sizeof(*xrep));

    xrep->xre_format = fmt;
    xrep->xre_fields = xfip;
    xrep->xre_num_fields = num_fields;

    /* Record the field info in the retain bucket */
    xrep->xre_next = xo_retain.xr_bucket[hash];
    xo_retain.xr_bucket[hash] = xrep;
    xo_retain_count += 1;
}