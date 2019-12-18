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
typedef  int /*<<< orphan*/  pmdval_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  __pmd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_mknotpresent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pmd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clear_pmd_presence(pmd_t *pmd, bool clear, pmdval_t *old)
{
	pmd_t new_pmd;
	pmdval_t v = pmd_val(*pmd);
	if (clear) {
		*old = v;
		new_pmd = pmd_mknotpresent(*pmd);
	} else {
		/* Presume this has been called with clear==true previously */
		new_pmd = __pmd(*old);
	}
	set_pmd(pmd, new_pmd);
}