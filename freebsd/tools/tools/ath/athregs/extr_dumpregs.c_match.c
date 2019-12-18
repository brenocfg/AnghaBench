#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dumpreg {int type; } ;
struct TYPE_3__ {int /*<<< orphan*/  ah_phyRev; int /*<<< orphan*/  ah_macRev; int /*<<< orphan*/  ah_macVersion; } ;
typedef  TYPE_1__ HAL_REVS ;

/* Variables and functions */
 int DUMP_BASEBAND ; 
 int /*<<< orphan*/  MAC_MATCH (struct dumpreg const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_MATCH (struct dumpreg const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline int
match(const struct dumpreg *dr, const HAL_REVS *revs)
{
	if (!MAC_MATCH(dr, revs->ah_macVersion, revs->ah_macRev))
		return 0;
	if ((dr->type & DUMP_BASEBAND) && !PHY_MATCH(dr, revs->ah_phyRev))
		return 0;
	return 1;
}