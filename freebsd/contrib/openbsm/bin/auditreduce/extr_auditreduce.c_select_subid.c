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

/* Variables and functions */
 scalar_t__ ISOPTSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPT_j ; 
 int /*<<< orphan*/  opttochk ; 
 int p_subid ; 

__attribute__((used)) static int
select_subid(int subid)
{

	/* Check if we want to select on subject uid. */
	if (ISOPTSET(opttochk, OPT_j)) {
		if (subid != p_subid)
			return (0);
	}
	return (1);
}