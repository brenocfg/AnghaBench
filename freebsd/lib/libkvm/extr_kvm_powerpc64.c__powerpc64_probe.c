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
struct TYPE_5__ {scalar_t__* e_ident; } ;
struct TYPE_6__ {TYPE_1__ nlehdr; } ;
typedef  TYPE_2__ kvm_t ;

/* Variables and functions */
 size_t EI_DATA ; 
 int /*<<< orphan*/  ELFCLASS64 ; 
 scalar_t__ ELFDATA2MSB ; 
 int /*<<< orphan*/  EM_PPC64 ; 
 scalar_t__ _kvm_probe_elf_kernel (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
_powerpc64_probe(kvm_t *kd)
{

	return (_kvm_probe_elf_kernel(kd, ELFCLASS64, EM_PPC64) &&
	    kd->nlehdr.e_ident[EI_DATA] == ELFDATA2MSB);
}