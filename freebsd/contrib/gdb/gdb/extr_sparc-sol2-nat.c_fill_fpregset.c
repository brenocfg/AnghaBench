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
typedef  int /*<<< orphan*/  prfpregset_t ;

/* Variables and functions */
 int /*<<< orphan*/  current_regcache ; 
 int /*<<< orphan*/  sparc_collect_fpregset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

void
fill_fpregset (prfpregset_t *fpregs, int regnum)
{
  sparc_collect_fpregset (current_regcache, regnum, fpregs);
}