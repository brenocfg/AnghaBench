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
struct mac_lomac {int ml_flags; int /*<<< orphan*/  ml_rangelow; int /*<<< orphan*/  ml_single; int /*<<< orphan*/  ml_rangehigh; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int MAC_LOMAC_FLAG_RANGE ; 
 int MAC_LOMAC_FLAG_SINGLE ; 
 scalar_t__ lomac_dominate_element (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
lomac_single_in_range(struct mac_lomac *single, struct mac_lomac *range)
{

	KASSERT((single->ml_flags & MAC_LOMAC_FLAG_SINGLE) != 0,
	    ("lomac_single_in_range: a not single"));
	KASSERT((range->ml_flags & MAC_LOMAC_FLAG_RANGE) != 0,
	    ("lomac_single_in_range: b not range"));

	return (lomac_dominate_element(&range->ml_rangehigh,
	    &single->ml_single) && lomac_dominate_element(&single->ml_single,
	    &range->ml_rangelow));
}