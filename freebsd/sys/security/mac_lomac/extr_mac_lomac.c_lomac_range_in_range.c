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
struct mac_lomac {int /*<<< orphan*/  ml_rangelow; int /*<<< orphan*/  ml_rangehigh; } ;

/* Variables and functions */
 scalar_t__ lomac_dominate_element (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
lomac_range_in_range(struct mac_lomac *rangea, struct mac_lomac *rangeb)
{

	return (lomac_dominate_element(&rangeb->ml_rangehigh,
	    &rangea->ml_rangehigh) &&
	    lomac_dominate_element(&rangea->ml_rangelow,
	    &rangeb->ml_rangelow));
}