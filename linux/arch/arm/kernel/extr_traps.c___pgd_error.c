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
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 scalar_t__ pgd_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,char const*,int,long long) ; 

void __pgd_error(const char *file, int line, pgd_t pgd)
{
	pr_err("%s:%d: bad pgd %08llx.\n", file, line, (long long)pgd_val(pgd));
}