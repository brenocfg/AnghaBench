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
struct spanhash {scalar_t__ hashval; int /*<<< orphan*/  cnt; } ;

/* Variables and functions */

__attribute__((used)) static int spanhash_cmp(const void *a_, const void *b_)
{
	const struct spanhash *a = a_;
	const struct spanhash *b = b_;

	/* A count of zero compares at the end.. */
	if (!a->cnt)
		return !b->cnt ? 0 : 1;
	if (!b->cnt)
		return -1;
	return a->hashval < b->hashval ? -1 :
		a->hashval > b->hashval ? 1 : 0;
}