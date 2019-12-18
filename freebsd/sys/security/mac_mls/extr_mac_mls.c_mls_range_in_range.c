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
struct mac_mls {int /*<<< orphan*/  mm_rangelow; int /*<<< orphan*/  mm_rangehigh; } ;

/* Variables and functions */
 scalar_t__ mls_dominate_element (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mls_range_in_range(struct mac_mls *rangea, struct mac_mls *rangeb)
{

	return (mls_dominate_element(&rangeb->mm_rangehigh,
	    &rangea->mm_rangehigh) &&
	    mls_dominate_element(&rangea->mm_rangelow,
	    &rangeb->mm_rangelow));
}