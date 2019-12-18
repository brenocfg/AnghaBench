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
struct unisve_bhli {scalar_t__ type; scalar_t__ len; int /*<<< orphan*/  info; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMON_OVERLAP (struct unisve_bhli const*,struct unisve_bhli const*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

int
unisve_overlap_bhli(const struct unisve_bhli *s1, const struct unisve_bhli *s2)
{
	COMMON_OVERLAP(s1, s2);

	return (s1->type == s2->type && s1->len == s2->len &&
	    memcmp(s1->info, s2->info, s1->len) == 0);
}