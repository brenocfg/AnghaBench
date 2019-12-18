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
struct eventtimer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPCPU_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cycles_per_tick ; 
 int /*<<< orphan*/  mips_wr_compare (int) ; 

__attribute__((used)) static int
clock_stop(struct eventtimer *et)
{

	DPCPU_SET(cycles_per_tick, 0);
	mips_wr_compare(0xffffffff);
	return (0);
}