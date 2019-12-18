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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  Elf32_Ehdr ;

/* Variables and functions */
 int /*<<< orphan*/  E_SHNUM ; 
 int /*<<< orphan*/  SH_SIZE ; 
 scalar_t__ elf_get_quarter (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ elf_get_word (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t
elf_get_shnum(Elf32_Ehdr *e, void *sh)
{
	uint64_t shnum;

	shnum = elf_get_quarter(e, e, E_SHNUM);
	if (shnum == 0)
		shnum = elf_get_word(e, (char *)sh, SH_SIZE);
	return shnum;
}