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
struct big_entries {scalar_t__* c; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_UNUSED (void*) ; 

__attribute__((used)) static int cmp_big(const void *_a, const void *_b, void *payload)
{
	const struct big_entries *a = (const struct big_entries *)_a, *b = (const struct big_entries *)_b;
	GIT_UNUSED(payload);
	return (a->c[0] < b->c[0]) ? -1 : (a->c[0] > b->c[0]) ? +1 : 0;
}