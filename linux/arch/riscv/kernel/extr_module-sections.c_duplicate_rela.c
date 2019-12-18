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
typedef  int /*<<< orphan*/  Elf_Rela ;

/* Variables and functions */
 scalar_t__ is_rela_equal (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static bool duplicate_rela(const Elf_Rela *rela, int idx)
{
	int i;
	for (i = 0; i < idx; i++) {
		if (is_rela_equal(&rela[i], &rela[idx]))
			return true;
	}
	return false;
}