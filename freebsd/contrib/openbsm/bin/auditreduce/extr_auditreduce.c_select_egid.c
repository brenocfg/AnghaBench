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
 int /*<<< orphan*/  OPT_f ; 
 int /*<<< orphan*/  opttochk ; 
 int p_egid ; 

__attribute__((used)) static int
select_egid(int egrp)
{

	/* Check if we want to select on egid. */
	if (ISOPTSET(opttochk, OPT_f)) {
		if (egrp != p_egid)
			return (0);
	}
	return (1);
}