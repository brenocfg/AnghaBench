#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ nsyms; } ;
struct file_info {TYPE_1__ dynsymtab; int /*<<< orphan*/  elf; TYPE_1__ symtab; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHT_DYNSYM ; 
 int /*<<< orphan*/  SHT_SYMTAB ; 
 int /*<<< orphan*/  load_symtab (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
load_symtabs(struct file_info *file)
{

	file->symtab.nsyms = file->dynsymtab.nsyms = 0;
	(void)load_symtab(file->elf, &file->symtab, SHT_SYMTAB);
	(void)load_symtab(file->elf, &file->dynsymtab, SHT_DYNSYM);
}