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
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*,char const*,int,long long) ; 
 scalar_t__ pte_val (int /*<<< orphan*/ ) ; 

void __pte_error(const char *file, int line, pte_t pte)
{
	pr_err("%s:%d: bad pte %08llx.\n", file, line, (long long)pte_val(pte));
}