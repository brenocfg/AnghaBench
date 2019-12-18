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
struct list_head {int /*<<< orphan*/  prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __list_add (struct list_head*,int /*<<< orphan*/ ,struct list_head*) ; 

__attribute__((used)) static inline void
list_add_tail(struct list_head *o, struct list_head *head)
{
        __list_add(o, head->prev, head);
}