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
 int /*<<< orphan*/  OPT_r ; 
 int /*<<< orphan*/  opttochk ; 
 int p_ruid ; 

__attribute__((used)) static int
select_ruid(int user)
{

	/* Check if we want to select on rgid. */
	if (ISOPTSET(opttochk, OPT_r)) {
		if (user != p_ruid)
			return (0);
	}
	return (1);
}