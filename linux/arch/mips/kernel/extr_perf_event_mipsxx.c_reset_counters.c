#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* write_counter ) (int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_1__ mipspmu ; 
 int /*<<< orphan*/  mipsxx_pmu_write_control (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reset_counters(void *arg)
{
	int counters = (int)(long)arg;
	switch (counters) {
	case 4:
		mipsxx_pmu_write_control(3, 0);
		mipspmu.write_counter(3, 0);
		/* fall through */
	case 3:
		mipsxx_pmu_write_control(2, 0);
		mipspmu.write_counter(2, 0);
		/* fall through */
	case 2:
		mipsxx_pmu_write_control(1, 0);
		mipspmu.write_counter(1, 0);
		/* fall through */
	case 1:
		mipsxx_pmu_write_control(0, 0);
		mipspmu.write_counter(0, 0);
		/* fall through */
	}
}