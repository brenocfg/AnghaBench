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
 scalar_t__ pte_ci (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_special (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_user (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int pte_looks_normal(pte_t pte)
{

	if (pte_present(pte) && !pte_special(pte)) {
		if (pte_ci(pte))
			return 0;
		if (pte_user(pte))
			return 1;
	}
	return 0;
}