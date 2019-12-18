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
typedef  size_t u_int ;
struct alg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  run_test (struct alg*,size_t) ; 

__attribute__((used)) static void
run_test_sizes(struct alg *alg, size_t *sizes, u_int nsizes)
{
	u_int i;

	for (i = 0; i < nsizes; i++)
		run_test(alg, sizes[i]);
}