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
struct keymap {int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
compare_keymap(const void *a, const void *b)
{

	/* We've been passed pointers to pointers, so: */
	const struct keymap *km1 = *((const struct keymap * const *) a);
	const struct keymap *km2 = *((const struct keymap * const *) b);

	return strcmp(km1->desc, km2->desc);
}