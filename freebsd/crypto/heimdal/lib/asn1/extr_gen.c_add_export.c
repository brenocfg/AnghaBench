#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sexport {char const* name; struct sexport* next; } ;

/* Variables and functions */
 struct sexport* emalloc (int) ; 
 struct sexport* exports ; 

void
add_export (const char *name)
{
    struct sexport *tmp = emalloc (sizeof(*tmp));

    tmp->name   = name;
    tmp->next   = exports;
    exports     = tmp;
}