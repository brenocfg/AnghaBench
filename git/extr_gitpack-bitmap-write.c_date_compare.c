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
struct commit {scalar_t__ date; } ;

/* Variables and functions */

__attribute__((used)) static int date_compare(const void *_a, const void *_b)
{
	struct commit *a = *(struct commit **)_a;
	struct commit *b = *(struct commit **)_b;
	return (long)b->date - (long)a->date;
}