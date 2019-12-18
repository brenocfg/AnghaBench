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
struct handle_split_cb_data {long tlno; long plno; int /*<<< orphan*/  split; int /*<<< orphan*/  parent; int /*<<< orphan*/  ent; int /*<<< orphan*/  sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  handle_split (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long,long,long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_split_cb(long start_a, long count_a,
			   long start_b, long count_b, void *data)
{
	struct handle_split_cb_data *d = data;
	handle_split(d->sb, d->ent, d->tlno, d->plno, start_b, d->parent,
		     d->split);
	d->plno = start_a + count_a;
	d->tlno = start_b + count_b;
	return 0;
}