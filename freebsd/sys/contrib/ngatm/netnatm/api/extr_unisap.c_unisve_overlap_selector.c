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
struct unisve_selector {scalar_t__ selector; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMON_OVERLAP (struct unisve_selector const*,struct unisve_selector const*) ; 

int
unisve_overlap_selector(const struct unisve_selector *s1,
    const struct unisve_selector *s2)
{
	COMMON_OVERLAP(s1, s2);

	return (s1->selector == s2->selector);
}