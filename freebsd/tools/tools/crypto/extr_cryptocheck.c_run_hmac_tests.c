#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct TYPE_4__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ T_HMAC ; 
 TYPE_1__* algs ; 
 size_t nitems (TYPE_1__*) ; 
 int /*<<< orphan*/  run_test_sizes (TYPE_1__*,size_t*,size_t) ; 

__attribute__((used)) static void
run_hmac_tests(size_t *sizes, u_int nsizes)
{
	u_int i;

	for (i = 0; i < nitems(algs); i++)
		if (algs[i].type == T_HMAC)
			run_test_sizes(&algs[i], sizes, nsizes);
}