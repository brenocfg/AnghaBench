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
struct TYPE_2__ {int /*<<< orphan*/  hash; } ;
struct ref {struct ref* next; TYPE_1__ old_oid; } ;

/* Variables and functions */
 scalar_t__ hasheq (int /*<<< orphan*/ ,unsigned char const*) ; 

__attribute__((used)) static int will_fetch(struct ref **head, const unsigned char *sha1)
{
	struct ref *rm = *head;
	while (rm) {
		if (hasheq(rm->old_oid.hash, sha1))
			return 1;
		rm = rm->next;
	}
	return 0;
}