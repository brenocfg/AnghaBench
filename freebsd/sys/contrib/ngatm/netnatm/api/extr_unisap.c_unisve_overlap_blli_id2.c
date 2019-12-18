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
struct unisve_blli_id2 {scalar_t__ proto; scalar_t__ user; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMON_OVERLAP (struct unisve_blli_id2 const*,struct unisve_blli_id2 const*) ; 
 scalar_t__ UNI_BLLI_L2_USER ; 

int
unisve_overlap_blli_id2(const struct unisve_blli_id2 *s1,
    const struct unisve_blli_id2 *s2)
{
	COMMON_OVERLAP(s1, s2);

	return (s1->proto == s2->proto &&
	    (s1->proto != UNI_BLLI_L2_USER || s1->user == s2->user));
}