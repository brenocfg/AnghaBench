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
struct outbound_list {int /*<<< orphan*/ * first; } ;

/* Variables and functions */

void 
outbound_list_init(struct outbound_list* list)
{
	list->first = NULL;
}