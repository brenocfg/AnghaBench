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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 en_stats_adder(__be64 *start, __be64 *next, int num)
{
	__be64 *curr = start;
	u64 ret = 0;
	int i;
	int offset = next - start;

	for (i = 0; i < num; i++) {
		ret += be64_to_cpu(*curr);
		curr += offset;
	}

	return ret;
}