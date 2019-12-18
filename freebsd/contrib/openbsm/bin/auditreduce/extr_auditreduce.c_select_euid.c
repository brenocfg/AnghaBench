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
 int /*<<< orphan*/  OPT_e ; 
 int /*<<< orphan*/  opttochk ; 
 int p_euid ; 

__attribute__((used)) static int
select_euid(int euser)
{

	/* Check if we want to select on euid. */
	if (ISOPTSET(opttochk, OPT_e)) {
		if (euser != p_euid)
			return (0);
	}
	return (1);
}