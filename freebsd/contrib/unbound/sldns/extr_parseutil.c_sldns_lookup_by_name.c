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
struct TYPE_4__ {int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ sldns_lookup_table ;

/* Variables and functions */
 scalar_t__ strcasecmp (char const*,int /*<<< orphan*/ *) ; 

sldns_lookup_table *
sldns_lookup_by_name(sldns_lookup_table *table, const char *name)
{
        while (table->name != NULL) {
                if (strcasecmp(name, table->name) == 0)
                        return table;
                table++;
        }
        return NULL;
}