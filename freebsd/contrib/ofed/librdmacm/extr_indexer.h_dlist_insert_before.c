#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  prev; } ;
typedef  TYPE_1__ dlist_entry ;

/* Variables and functions */
 int /*<<< orphan*/  dlist_insert_after (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void dlist_insert_before(dlist_entry *item, dlist_entry *head)
{
	dlist_insert_after(item, head->prev);
}