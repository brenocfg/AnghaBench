#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  linker_file_t ;
typedef  TYPE_2__* elf_file_t ;
struct TYPE_6__ {scalar_t__ l_name; int /*<<< orphan*/ * l_ld; } ;
struct TYPE_5__ {scalar_t__ pcpu_base; scalar_t__ vnet_base; void* address; void* symbase; void* strbase; void* ctftab; void* ctfoff; void* typoff; TYPE_1__* object; scalar_t__ preloaded; TYPE_3__ gdb; scalar_t__ vnet_start; scalar_t__ vnet_stop; scalar_t__ pcpu_start; scalar_t__ pcpu_stop; } ;
struct TYPE_4__ {int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  GDB_STATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_LINKER ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  RT_CONSISTENT ; 
 int /*<<< orphan*/  RT_DELETE ; 
 int /*<<< orphan*/  dpcpu_free (void*,scalar_t__) ; 
 int /*<<< orphan*/  elf_cpu_unload_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elf_set_delete (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  free (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernel_map ; 
 int /*<<< orphan*/  link_elf_delete_gdb (TYPE_3__*) ; 
 int /*<<< orphan*/  link_elf_unload_preload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pcpu_list ; 
 int /*<<< orphan*/  set_vnet_list ; 
 int /*<<< orphan*/  vm_map_remove (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  vnet_data_free (void*,scalar_t__) ; 

__attribute__((used)) static void
link_elf_unload_file(linker_file_t file)
{
	elf_file_t ef = (elf_file_t) file;

	if (ef->pcpu_base != 0) {
		dpcpu_free((void *)ef->pcpu_base,
		    ef->pcpu_stop - ef->pcpu_start);
		elf_set_delete(&set_pcpu_list, ef->pcpu_start);
	}
#ifdef VIMAGE
	if (ef->vnet_base != 0) {
		vnet_data_free((void *)ef->vnet_base,
		    ef->vnet_stop - ef->vnet_start);
		elf_set_delete(&set_vnet_list, ef->vnet_start);
	}
#endif
#ifdef GDB
	if (ef->gdb.l_ld != NULL) {
		GDB_STATE(RT_DELETE);
		free((void *)(uintptr_t)ef->gdb.l_name, M_LINKER);
		link_elf_delete_gdb(&ef->gdb);
		GDB_STATE(RT_CONSISTENT);
	}
#endif

	/* Notify MD code that a module is being unloaded. */
	elf_cpu_unload_file(file);

	if (ef->preloaded) {
		link_elf_unload_preload(file);
		return;
	}

#ifdef SPARSE_MAPPING
	if (ef->object != NULL) {
		vm_map_remove(kernel_map, (vm_offset_t) ef->address,
		    (vm_offset_t) ef->address
		    + (ef->object->size << PAGE_SHIFT));
	}
#else
	free(ef->address, M_LINKER);
#endif
	free(ef->symbase, M_LINKER);
	free(ef->strbase, M_LINKER);
	free(ef->ctftab, M_LINKER);
	free(ef->ctfoff, M_LINKER);
	free(ef->typoff, M_LINKER);
}