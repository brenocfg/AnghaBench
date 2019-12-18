#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* elf_file_t ;
struct TYPE_5__ {scalar_t__ p_vaddr; scalar_t__ p_memsz; scalar_t__ p_offset; } ;
struct TYPE_4__ {int ef_nsegs; TYPE_2__** ef_segs; } ;
typedef  TYPE_2__ Elf_Phdr ;
typedef  scalar_t__ Elf_Off ;

/* Variables and functions */

__attribute__((used)) static Elf_Off
ef_get_offset(elf_file_t ef, Elf_Off off)
{
	Elf_Phdr *ph;
	int i;

	for (i = 0; i < ef->ef_nsegs; i++) {
		ph = ef->ef_segs[i];
		if (off >= ph->p_vaddr && off < ph->p_vaddr + ph->p_memsz) {
			return (ph->p_offset + (off - ph->p_vaddr));
		}
	}
	return (0);
}