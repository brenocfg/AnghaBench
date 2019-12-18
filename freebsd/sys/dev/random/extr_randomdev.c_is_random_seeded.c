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
struct TYPE_2__ {int (* ra_seeded ) () ;} ;

/* Variables and functions */
 TYPE_1__* p_random_alg_context ; 
 int stub1 () ; 

bool
IS_RANDOM_SEEDED(void)
{
	return (p_random_alg_context->ra_seeded());
}