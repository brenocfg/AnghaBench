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
struct TYPE_2__ {scalar_t__ type; scalar_t__ hash; scalar_t__ size; } ;
typedef  TYPE_1__ git_pobject ;

/* Variables and functions */

__attribute__((used)) static int type_size_sort(const void *_a, const void *_b)
{
	const git_pobject *a = (git_pobject *)_a;
	const git_pobject *b = (git_pobject *)_b;

	if (a->type > b->type)
		return -1;
	if (a->type < b->type)
		return 1;
	if (a->hash > b->hash)
		return -1;
	if (a->hash < b->hash)
		return 1;
	/*
	 * TODO
	 *
	if (a->preferred_base > b->preferred_base)
		return -1;
	if (a->preferred_base < b->preferred_base)
		return 1;
	*/
	if (a->size > b->size)
		return -1;
	if (a->size < b->size)
		return 1;
	return a < b ? -1 : (a > b); /* newest first */
}