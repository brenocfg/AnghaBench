#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t nlist; int /*<<< orphan*/ ** list; } ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 scalar_t__ Strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__ tw_item ; 

Char *
tw_item_find(Char *str)
{
    size_t i;

    if (tw_item.list == NULL || str == NULL)
	return NULL;

    for (i = 0; i < tw_item.nlist; i++)
	if (tw_item.list[i] != NULL && Strcmp(tw_item.list[i], str) == 0)
	    return tw_item.list[i];
    return NULL;
}