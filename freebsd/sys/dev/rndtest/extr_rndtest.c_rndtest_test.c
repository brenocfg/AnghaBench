#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rndtest_state {int rs_discard; } ;
struct TYPE_4__ {int /*<<< orphan*/  rst_tests; } ;
struct TYPE_3__ {int (* test ) (struct rndtest_state*) ;} ;

/* Variables and functions */
 int RNDTEST_NTESTS ; 
 TYPE_2__ rndstats ; 
 TYPE_1__* rndtest_funcs ; 
 int stub1 (struct rndtest_state*) ; 

__attribute__((used)) static void
rndtest_test(struct rndtest_state *rsp)
{
	int i, rv = 0;

	rndstats.rst_tests++;
	for (i = 0; i < RNDTEST_NTESTS; i++)
		rv |= (*rndtest_funcs[i].test)(rsp);
	rsp->rs_discard = (rv != 0);
}