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
struct vdso_elfinfo64 {int dummy; } ;
struct TYPE_4__ {struct vdso_elfinfo64 elf64; } ;
struct vdso_elfinfo {TYPE_1__ u; } ;
struct TYPE_5__ {int /*<<< orphan*/  st_shndx; int /*<<< orphan*/  st_other; int /*<<< orphan*/  st_info; int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_value; } ;
typedef  TYPE_2__ Elf64_Sym ;

/* Variables and functions */
 int ENODEV ; 
 TYPE_2__* find_sym64 (struct vdso_elfinfo64*,char const*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int patchsym64(struct vdso_elfinfo *_e, const char *orig,
		      const char *new)
{
	struct vdso_elfinfo64 *e = &_e->u.elf64;
	Elf64_Sym *osym = find_sym64(e, orig);
	Elf64_Sym *nsym = find_sym64(e, new);

	if (!nsym || !osym) {
		pr_err("VDSO64: Missing symbols.\n");
		return -ENODEV;
	}
	osym->st_value = nsym->st_value;
	osym->st_size = nsym->st_size;
	osym->st_info = nsym->st_info;
	osym->st_other = nsym->st_other;
	osym->st_shndx = nsym->st_shndx;

	return 0;
}