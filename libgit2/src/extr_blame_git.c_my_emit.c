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
struct TYPE_2__ {long tlno; long plno; int /*<<< orphan*/  parent; int /*<<< orphan*/  target; int /*<<< orphan*/  blame; } ;
typedef  TYPE_1__ blame_chunk_cb_data ;

/* Variables and functions */
 scalar_t__ blame_chunk (int /*<<< orphan*/ ,long,long,long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int my_emit(
	long start_a, long count_a,
	long start_b, long count_b,
	void *cb_data)
{
	blame_chunk_cb_data *d = (blame_chunk_cb_data *)cb_data;

	if (blame_chunk(d->blame, d->tlno, d->plno, start_b, d->target, d->parent) < 0)
		return -1;
	d->plno = start_a + count_a;
	d->tlno = start_b + count_b;

	return 0;
}