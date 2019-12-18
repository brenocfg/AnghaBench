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
typedef  int /*<<< orphan*/  pud_t ;

/* Variables and functions */
 int _PAGE_EXEC ; 
 int _PAGE_READ ; 
 int _PAGE_WRITE ; 
 scalar_t__ pud_present (int /*<<< orphan*/ ) ; 
 int pud_val (int /*<<< orphan*/ ) ; 

int pud_huge(pud_t pud)
{
	return pud_present(pud) &&
		(pud_val(pud) & (_PAGE_READ | _PAGE_WRITE | _PAGE_EXEC));
}