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
struct volatile_list_head {int /*<<< orphan*/  next; int /*<<< orphan*/  prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __volatile_list_del (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void volatile_list_del(volatile struct volatile_list_head *elem)
{
	__volatile_list_del(elem->prev, elem->next);
}