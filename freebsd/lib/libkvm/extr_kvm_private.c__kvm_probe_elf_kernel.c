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
struct TYPE_4__ {int* e_ident; scalar_t__ e_type; int e_machine; } ;
struct TYPE_5__ {TYPE_1__ nlehdr; } ;
typedef  TYPE_2__ kvm_t ;

/* Variables and functions */
 size_t EI_CLASS ; 
 int EM_PPC ; 
 int EM_PPC64 ; 
 scalar_t__ ET_DYN ; 
 scalar_t__ ET_EXEC ; 

int
_kvm_probe_elf_kernel(kvm_t *kd, int class, int machine)
{

	return (kd->nlehdr.e_ident[EI_CLASS] == class &&
	    ((machine == EM_PPC || machine == EM_PPC64) ?
	     kd->nlehdr.e_type == ET_DYN : kd->nlehdr.e_type == ET_EXEC) &&
	    kd->nlehdr.e_machine == machine);
}