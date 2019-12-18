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
typedef  void* u_long ;
struct TYPE_4__ {scalar_t__ a_ptr; int /*<<< orphan*/  a_val; } ;
struct TYPE_5__ {int a_type; TYPE_1__ a_un; } ;
typedef  TYPE_2__ Elf_Auxinfo ;

/* Variables and functions */
#define  AT_CANARY 138 
#define  AT_CANARYLEN 137 
#define  AT_EXECPATH 136 
#define  AT_HWCAP 135 
#define  AT_HWCAP2 134 
#define  AT_NCPUS 133 
 int AT_NULL ; 
#define  AT_OSRELDATE 132 
#define  AT_PAGESIZES 131 
#define  AT_PAGESIZESLEN 130 
#define  AT_PAGESZ 129 
#define  AT_TIMEKEEP 128 
 TYPE_2__* __elf_aux_vector ; 
 char* canary ; 
 int /*<<< orphan*/  canary_len ; 
 char* execpath ; 
 void* hwcap ; 
 void* hwcap2 ; 
 int hwcap2_present ; 
 int hwcap_present ; 
 int /*<<< orphan*/  ncpus ; 
 int /*<<< orphan*/  osreldate ; 
 int /*<<< orphan*/  pagesize ; 
 char* pagesizes ; 
 int /*<<< orphan*/  pagesizes_len ; 
 scalar_t__ timekeep ; 

__attribute__((used)) static void
init_aux(void)
{
	Elf_Auxinfo *aux;

	for (aux = __elf_aux_vector; aux->a_type != AT_NULL; aux++) {
		switch (aux->a_type) {
		case AT_CANARY:
			canary = (char *)(aux->a_un.a_ptr);
			break;

		case AT_CANARYLEN:
			canary_len = aux->a_un.a_val;
			break;

		case AT_EXECPATH:
			execpath = (char *)(aux->a_un.a_ptr);
			break;

		case AT_HWCAP:
			hwcap_present = 1;
			hwcap = (u_long)(aux->a_un.a_val);
			break;

		case AT_HWCAP2:
			hwcap2_present = 1;
			hwcap2 = (u_long)(aux->a_un.a_val);
			break;

		case AT_PAGESIZES:
			pagesizes = (char *)(aux->a_un.a_ptr);
			break;

		case AT_PAGESIZESLEN:
			pagesizes_len = aux->a_un.a_val;
			break;

		case AT_PAGESZ:
			pagesize = aux->a_un.a_val;
			break;

		case AT_OSRELDATE:
			osreldate = aux->a_un.a_val;
			break;

		case AT_NCPUS:
			ncpus = aux->a_un.a_val;
			break;

		case AT_TIMEKEEP:
			timekeep = aux->a_un.a_ptr;
			break;
		}
	}
}