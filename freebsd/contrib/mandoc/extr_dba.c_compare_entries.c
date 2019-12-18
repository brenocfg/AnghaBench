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
struct macro_entry {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
compare_entries(const void *vp1, const void *vp2)
{
	const struct macro_entry *ep1, *ep2;

	ep1 = *(const struct macro_entry * const *)vp1;
	ep2 = *(const struct macro_entry * const *)vp2;
	return strcmp(ep1->value, ep2->value);
}