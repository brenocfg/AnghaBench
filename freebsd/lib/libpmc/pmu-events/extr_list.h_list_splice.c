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
struct list_head {int /*<<< orphan*/  next; } ;

/* Variables and functions */
 int /*<<< orphan*/  linux_list_splice (struct list_head const*,struct list_head*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
list_splice(const struct list_head *list, struct list_head *head)
{

	linux_list_splice(list, head, head->next);
}