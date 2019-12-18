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
struct limit {int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 struct limit* limits ; 
 scalar_t__ strcasecmp (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct limit *
find_limit(const char *name)
{
    struct limit *l;
    for(l = limits; l->name != NULL; l++)
	if(strcasecmp(name, l->name) == 0)
	    return l;
    return NULL;
}