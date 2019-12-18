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
typedef  int u_int32_t ;
struct fm801_info {int /*<<< orphan*/  sh; int /*<<< orphan*/  st; } ;

/* Variables and functions */
 int bus_space_read_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int bus_space_read_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u_int32_t
fm801_rd(struct fm801_info *fm801, int regno, int size)
{
	switch(size) {
	case 1:
		return (bus_space_read_1(fm801->st, fm801->sh, regno));
	case 2:
		return (bus_space_read_2(fm801->st, fm801->sh, regno));
	case 4:
		return (bus_space_read_4(fm801->st, fm801->sh, regno));
	default:
		return 0xffffffff;
	}
}