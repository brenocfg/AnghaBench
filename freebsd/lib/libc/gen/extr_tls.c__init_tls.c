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
struct TYPE_4__ {size_t a_val; TYPE_2__* a_ptr; } ;
struct TYPE_6__ {int a_type; TYPE_1__ a_un; } ;
struct TYPE_5__ {scalar_t__ p_type; scalar_t__ p_vaddr; int /*<<< orphan*/  p_align; int /*<<< orphan*/  p_filesz; int /*<<< orphan*/  p_memsz; } ;
typedef  TYPE_2__ Elf_Phdr ;
typedef  TYPE_3__ Elf_Auxinfo ;
typedef  int /*<<< orphan*/  Elf_Addr ;

/* Variables and functions */
 int AT_NULL ; 
#define  AT_PHDR 130 
#define  AT_PHENT 129 
#define  AT_PHNUM 128 
 scalar_t__ PT_TLS ; 
 int /*<<< orphan*/  TLS_TCB_ALIGN ; 
 int /*<<< orphan*/  TLS_TCB_SIZE ; 
 void* _rtld_allocate_tls (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _set_tp (void*) ; 
 scalar_t__ environ ; 
 int /*<<< orphan*/  roundup2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* tls_init ; 
 int /*<<< orphan*/  tls_init_align ; 
 int /*<<< orphan*/  tls_init_size ; 
 int /*<<< orphan*/  tls_static_space ; 

void
_init_tls(void)
{
#ifndef PIC
	Elf_Addr *sp;
	Elf_Auxinfo *aux, *auxp;
	Elf_Phdr *phdr;
	size_t phent, phnum;
	int i;
	void *tls;

	sp = (Elf_Addr *) environ;
	while (*sp++ != 0)
		;
	aux = (Elf_Auxinfo *) sp;
	phdr = NULL;
	phent = phnum = 0;
	for (auxp = aux; auxp->a_type != AT_NULL; auxp++) {
		switch (auxp->a_type) {
		case AT_PHDR:
			phdr = auxp->a_un.a_ptr;
			break;

		case AT_PHENT:
			phent = auxp->a_un.a_val;
			break;

		case AT_PHNUM:
			phnum = auxp->a_un.a_val;
			break;
		}
	}
	if (phdr == NULL || phent != sizeof(Elf_Phdr) || phnum == 0)
		return;

	for (i = 0; (unsigned) i < phnum; i++) {
		if (phdr[i].p_type == PT_TLS) {
			tls_static_space = roundup2(phdr[i].p_memsz,
			    phdr[i].p_align);
			tls_init_size = phdr[i].p_filesz;
			tls_init_align = phdr[i].p_align;
			tls_init = (void*) phdr[i].p_vaddr;
			break;
		}
	}
	tls = _rtld_allocate_tls(NULL, TLS_TCB_SIZE, TLS_TCB_ALIGN);

	_set_tp(tls);
#endif
}