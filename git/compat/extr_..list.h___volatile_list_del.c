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
struct volatile_list_head {struct volatile_list_head volatile* next; struct volatile_list_head volatile* prev; } ;

/* Variables and functions */

__attribute__((used)) static inline void __volatile_list_del(volatile struct volatile_list_head *prev,
				       volatile struct volatile_list_head *next)
{
	next->prev = prev;
	prev->next = next;
}