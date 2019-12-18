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
struct ref {struct ref* next; int /*<<< orphan*/  old_oid; } ;
struct oidset {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  oidset_insert (struct oidset*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void create_fetch_oidset(struct ref **head, struct oidset *out)
{
	struct ref *rm = *head;
	while (rm) {
		oidset_insert(out, &rm->old_oid);
		rm = rm->next;
	}
}