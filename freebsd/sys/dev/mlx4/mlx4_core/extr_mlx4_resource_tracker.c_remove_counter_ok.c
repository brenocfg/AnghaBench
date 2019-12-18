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
struct TYPE_2__ {scalar_t__ state; } ;
struct res_counter {TYPE_1__ com; } ;

/* Variables and functions */
 int EBUSY ; 
 int EPERM ; 
 scalar_t__ RES_COUNTER_ALLOCATED ; 
 scalar_t__ RES_COUNTER_BUSY ; 

__attribute__((used)) static int remove_counter_ok(struct res_counter *res)
{
	if (res->com.state == RES_COUNTER_BUSY)
		return -EBUSY;
	else if (res->com.state != RES_COUNTER_ALLOCATED)
		return -EPERM;

	return 0;
}