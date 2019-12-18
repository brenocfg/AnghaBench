#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  uintmax_t ;
struct TYPE_5__ {int e_phnum; } ;
struct procstat_core {scalar_t__ pc_magic; int /*<<< orphan*/  pc_elf; TYPE_1__ pc_ehdr; } ;
typedef  int ssize_t ;
typedef  scalar_t__ off_t ;
struct TYPE_6__ {scalar_t__ p_type; scalar_t__ p_vaddr; scalar_t__ p_memsz; scalar_t__ p_offset; } ;
typedef  TYPE_2__ GElf_Phdr ;

/* Variables and functions */
 scalar_t__ PROCSTAT_CORE_MAGIC ; 
 scalar_t__ PT_LOAD ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  core_offset (struct procstat_core*,scalar_t__) ; 
 int /*<<< orphan*/  core_read (struct procstat_core*,void*,size_t) ; 
 int /*<<< orphan*/  elf_errmsg (int) ; 
 TYPE_2__* gelf_getphdr (int /*<<< orphan*/ ,int,TYPE_2__*) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static ssize_t
core_read_mem(struct procstat_core *core, void *buf, size_t len,
    vm_offset_t addr, bool readall)
{
	GElf_Phdr phdr;
	off_t offset;
	int i;

	assert(core->pc_magic == PROCSTAT_CORE_MAGIC);

	for (i = 0; i < core->pc_ehdr.e_phnum; i++) {
		if (gelf_getphdr(core->pc_elf, i, &phdr) != &phdr) {
			warnx("gelf_getphdr: %s", elf_errmsg(-1));
			return (-1);
		}
		if (phdr.p_type != PT_LOAD)
			continue;
		if (addr < phdr.p_vaddr || addr > phdr.p_vaddr + phdr.p_memsz)
			continue;
		offset = phdr.p_offset + (addr - phdr.p_vaddr);
		if ((phdr.p_vaddr + phdr.p_memsz) - addr < len) {
			if (readall) {
				warnx("format error: "
				    "attempt to read out of segment");
				return (-1);
			}
			len = (phdr.p_vaddr + phdr.p_memsz) - addr;
		}
		if (!core_offset(core, offset))
			return (-1);
		if (!core_read(core, buf, len))
			return (-1);
		return (len);
	}
	warnx("format error: address %ju not found", (uintmax_t)addr);
	return (-1);
}