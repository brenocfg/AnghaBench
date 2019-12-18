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
struct mac_lomac_element {scalar_t__ mle_type; scalar_t__ mle_grade; } ;

/* Variables and functions */
 scalar_t__ MAC_LOMAC_TYPE_EQUAL ; 

__attribute__((used)) static int
lomac_equal_element(struct mac_lomac_element *a, struct mac_lomac_element *b)
{

	if (a->mle_type == MAC_LOMAC_TYPE_EQUAL ||
	    b->mle_type == MAC_LOMAC_TYPE_EQUAL)
		return (1);

	return (a->mle_type == b->mle_type && a->mle_grade == b->mle_grade);
}