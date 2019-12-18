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
 int /*<<< orphan*/  __rste_to_pte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_val (int /*<<< orphan*/ ) ; 

pte_t huge_ptep_get(pte_t *ptep)
{
	return __rste_to_pte(pte_val(*ptep));
}