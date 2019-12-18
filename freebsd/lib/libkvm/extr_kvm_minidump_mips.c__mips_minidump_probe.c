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
struct TYPE_5__ {scalar_t__* e_ident; scalar_t__ e_machine; } ;
struct TYPE_6__ {TYPE_1__ nlehdr; } ;
typedef  TYPE_2__ kvm_t ;

/* Variables and functions */
 size_t EI_CLASS ; 
 scalar_t__ ELFCLASS32 ; 
 scalar_t__ ELFCLASS64 ; 
 scalar_t__ EM_MIPS ; 
 int _kvm_is_minidump (TYPE_2__*) ; 

__attribute__((used)) static int
_mips_minidump_probe(kvm_t *kd)
{

	if (kd->nlehdr.e_ident[EI_CLASS] != ELFCLASS32 &&
	    kd->nlehdr.e_ident[EI_CLASS] != ELFCLASS64)
		return (0);
	if (kd->nlehdr.e_machine != EM_MIPS)
		return (0);
	return (_kvm_is_minidump(kd));
}