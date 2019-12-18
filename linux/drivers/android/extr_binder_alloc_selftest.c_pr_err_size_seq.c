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
 int BUFFER_NUM ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static void pr_err_size_seq(size_t *sizes, int *seq)
{
	int i;

	pr_err("alloc sizes: ");
	for (i = 0; i < BUFFER_NUM; i++)
		pr_cont("[%zu]", sizes[i]);
	pr_cont("\n");
	pr_err("free seq: ");
	for (i = 0; i < BUFFER_NUM; i++)
		pr_cont("[%d]", seq[i]);
	pr_cont("\n");
}