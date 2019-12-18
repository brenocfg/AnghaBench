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
struct mac_biba {int /*<<< orphan*/  mb_rangelow; int /*<<< orphan*/  mb_rangehigh; } ;

/* Variables and functions */
 scalar_t__ biba_dominate_element (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
biba_range_in_range(struct mac_biba *rangea, struct mac_biba *rangeb)
{

	return (biba_dominate_element(&rangeb->mb_rangehigh,
	    &rangea->mb_rangehigh) &&
	    biba_dominate_element(&rangea->mb_rangelow,
	    &rangeb->mb_rangelow));
}