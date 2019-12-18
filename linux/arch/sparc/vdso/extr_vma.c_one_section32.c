#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vdso_elfinfo32 {TYPE_1__* hdr; } ;
struct TYPE_4__ {int sh_offset; int sh_name; unsigned long sh_size; } ;
struct TYPE_3__ {int e_shoff; size_t e_shstrndx; unsigned int e_shnum; } ;
typedef  TYPE_2__ Elf32_Shdr ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 

__attribute__((used)) static void *one_section32(struct vdso_elfinfo32 *e, const char *name,
			   unsigned long *size)
{
	const char *snames;
	Elf32_Shdr *shdrs;
	unsigned int i;

	shdrs = (void *)e->hdr + e->hdr->e_shoff;
	snames = (void *)e->hdr + shdrs[e->hdr->e_shstrndx].sh_offset;
	for (i = 1; i < e->hdr->e_shnum; i++) {
		if (!strcmp(snames+shdrs[i].sh_name, name)) {
			if (size)
				*size = shdrs[i].sh_size;
			return (void *)e->hdr + shdrs[i].sh_offset;
		}
	}
	return NULL;
}