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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_DPOP (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int __is_power_of_two(uint64_t v)
{
	int num_of_1s = 0;

	CVMX_DPOP(num_of_1s, v);
	return (num_of_1s  ==  1 );
}