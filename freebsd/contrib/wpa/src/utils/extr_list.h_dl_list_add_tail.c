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
struct dl_list {int /*<<< orphan*/  prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dl_list_add (int /*<<< orphan*/ ,struct dl_list*) ; 

__attribute__((used)) static inline void dl_list_add_tail(struct dl_list *list, struct dl_list *item)
{
	dl_list_add(list->prev, item);
}