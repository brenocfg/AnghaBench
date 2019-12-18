#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
typedef  size_t u_int ;
typedef  TYPE_2__* linker_file_t ;
typedef  TYPE_3__* elf_file_t ;
struct TYPE_10__ {scalar_t__ size; struct TYPE_10__* rela; struct TYPE_10__* rel; int /*<<< orphan*/  addr; int /*<<< orphan*/ * name; } ;
struct TYPE_9__ {size_t nprogtab; size_t nreltab; size_t nrelatab; TYPE_5__* typoff; TYPE_5__* ctfoff; TYPE_5__* ctftab; TYPE_5__* shstrtab; TYPE_5__* ddbstrtab; TYPE_5__* ddbsymtab; TYPE_5__* e_shdr; TYPE_1__* object; scalar_t__ address; TYPE_5__* progtab; TYPE_5__* relatab; TYPE_5__* reltab; scalar_t__ preloaded; } ;
struct TYPE_8__ {int /*<<< orphan*/ * pathname; } ;
struct TYPE_7__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPCPU_SETNAME ; 
 int /*<<< orphan*/  M_LINKER ; 
 int /*<<< orphan*/  VNET_SETNAME ; 
 int /*<<< orphan*/  dpcpu_free (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  elf_cpu_unload_file (TYPE_2__*) ; 
 int /*<<< orphan*/  free (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernel_map ; 
 int /*<<< orphan*/  preload_delete_name (int /*<<< orphan*/ *) ; 
 scalar_t__ ptoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_remove (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  vnet_data_free (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
link_elf_unload_file(linker_file_t file)
{
	elf_file_t ef = (elf_file_t) file;
	u_int i;

	/* Notify MD code that a module is being unloaded. */
	elf_cpu_unload_file(file);

	if (ef->progtab) {
		for (i = 0; i < ef->nprogtab; i++) {
			if (ef->progtab[i].size == 0)
				continue;
			if (ef->progtab[i].name == NULL)
				continue;
			if (!strcmp(ef->progtab[i].name, DPCPU_SETNAME))
				dpcpu_free(ef->progtab[i].addr,
				    ef->progtab[i].size);
#ifdef VIMAGE
			else if (!strcmp(ef->progtab[i].name, VNET_SETNAME))
				vnet_data_free(ef->progtab[i].addr,
				    ef->progtab[i].size);
#endif
		}
	}
	if (ef->preloaded) {
		free(ef->reltab, M_LINKER);
		free(ef->relatab, M_LINKER);
		free(ef->progtab, M_LINKER);
		free(ef->ctftab, M_LINKER);
		free(ef->ctfoff, M_LINKER);
		free(ef->typoff, M_LINKER);
		if (file->pathname != NULL)
			preload_delete_name(file->pathname);
		return;
	}

	for (i = 0; i < ef->nreltab; i++)
		free(ef->reltab[i].rel, M_LINKER);
	for (i = 0; i < ef->nrelatab; i++)
		free(ef->relatab[i].rela, M_LINKER);
	free(ef->reltab, M_LINKER);
	free(ef->relatab, M_LINKER);
	free(ef->progtab, M_LINKER);

	if (ef->object != NULL)
		vm_map_remove(kernel_map, (vm_offset_t)ef->address,
		    (vm_offset_t)ef->address + ptoa(ef->object->size));
	free(ef->e_shdr, M_LINKER);
	free(ef->ddbsymtab, M_LINKER);
	free(ef->ddbstrtab, M_LINKER);
	free(ef->shstrtab, M_LINKER);
	free(ef->ctftab, M_LINKER);
	free(ef->ctfoff, M_LINKER);
	free(ef->typoff, M_LINKER);
}