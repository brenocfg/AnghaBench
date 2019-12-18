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
struct mem_vector {scalar_t__ start; scalar_t__ size; } ;

/* Variables and functions */

__attribute__((used)) static bool mem_overlaps(struct mem_vector *one, struct mem_vector *two)
{
	/* Item one is entirely before item two. */
	if (one->start + one->size <= two->start)
		return false;
	/* Item one is entirely after item two. */
	if (one->start >= two->start + two->size)
		return false;
	return true;
}