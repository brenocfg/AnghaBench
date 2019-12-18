#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* extensions; } ;
typedef  TYPE_3__ hdb_entry ;
struct TYPE_7__ {unsigned int element; } ;
struct TYPE_10__ {TYPE_1__ data; } ;
struct TYPE_8__ {size_t len; TYPE_4__* val; } ;
typedef  TYPE_4__ HDB_extension ;

/* Variables and functions */

HDB_extension *
hdb_find_extension(const hdb_entry *entry, int type)
{
    size_t i;

    if (entry->extensions == NULL)
	return NULL;

    for (i = 0; i < entry->extensions->len; i++)
	if (entry->extensions->val[i].data.element == (unsigned)type)
	    return &entry->extensions->val[i];
    return NULL;
}