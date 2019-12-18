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
struct bitset {int dummy; } ;
typedef  int /*<<< orphan*/  cpuset_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_LEVEL_ROOT ; 
 int /*<<< orphan*/  CPU_SETSIZE ; 
 int /*<<< orphan*/  CPU_WHICH_PID ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 scalar_t__ cpuset_getaffinity (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  parselist (char*,struct bitset*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcasecmp (char*,char*) ; 

__attribute__((used)) static void
parsecpulist(char *list, cpuset_t *mask)
{

	if (strcasecmp(list, "all") == 0) {
		if (cpuset_getaffinity(CPU_LEVEL_ROOT, CPU_WHICH_PID, -1,
		    sizeof(*mask), mask) != 0)
			err(EXIT_FAILURE, "getaffinity");
		return;
	}
	parselist(list, (struct bitset *)mask, CPU_SETSIZE);
}