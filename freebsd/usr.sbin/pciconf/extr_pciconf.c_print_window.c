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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
print_window(int reg, const char *type, int range, uint64_t base,
    uint64_t limit)
{

	printf("    window[%02x] = type %s, range %2d, addr %#jx-%#jx, %s\n",
	    reg, type, range, (uintmax_t)base, (uintmax_t)limit,
	    base < limit ? "enabled" : "disabled");
}