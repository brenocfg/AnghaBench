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

/* Variables and functions */
 int /*<<< orphan*/  R4000_WAR ; 
 int /*<<< orphan*/  bug64hit ; 
 int /*<<< orphan*/  mult_sh_align_mod (long*,long*,long*,int,int) ; 
 int /*<<< orphan*/  nowar ; 
 int /*<<< orphan*/  panic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_cont (char*) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  r4kwar ; 

void check_mult_sh(void)
{
	long v1[8], v2[8], w[8];
	int bug, fix, i;

	printk("Checking for the multiply/shift bug... ");

	/*
	 * Testing discovered false negatives for certain code offsets
	 * into cache lines.  Hence we test all possible offsets for
	 * the worst assumption of an R4000 I-cache line width of 32
	 * bytes.
	 *
	 * We can't use a loop as alignment directives need to be
	 * immediates.
	 */
	mult_sh_align_mod(&v1[0], &v2[0], &w[0], 32, 0);
	mult_sh_align_mod(&v1[1], &v2[1], &w[1], 32, 1);
	mult_sh_align_mod(&v1[2], &v2[2], &w[2], 32, 2);
	mult_sh_align_mod(&v1[3], &v2[3], &w[3], 32, 3);
	mult_sh_align_mod(&v1[4], &v2[4], &w[4], 32, 4);
	mult_sh_align_mod(&v1[5], &v2[5], &w[5], 32, 5);
	mult_sh_align_mod(&v1[6], &v2[6], &w[6], 32, 6);
	mult_sh_align_mod(&v1[7], &v2[7], &w[7], 32, 7);

	bug = 0;
	for (i = 0; i < 8; i++)
		if (v1[i] != w[i])
			bug = 1;

	if (bug == 0) {
		pr_cont("no.\n");
		return;
	}

	pr_cont("yes, workaround... ");

	fix = 1;
	for (i = 0; i < 8; i++)
		if (v2[i] != w[i])
			fix = 0;

	if (fix == 1) {
		pr_cont("yes.\n");
		return;
	}

	pr_cont("no.\n");
	panic(bug64hit, !R4000_WAR ? r4kwar : nowar);
}