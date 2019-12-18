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
typedef  void* uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  a_val; } ;
struct TYPE_4__ {int a_type; TYPE_1__ a_un; } ;
typedef  TYPE_2__ Elf_Auxinfo ;

/* Variables and functions */
#define  AT_HWCAP 129 
#define  AT_HWCAP2 128 
 int AT_NULL ; 
 void* cpu_features ; 
 void* cpu_features2 ; 

__attribute__((used)) static void
init_cpu_features(char **env)
{
	const Elf_Auxinfo *aux;

	/* Find the auxiliary vector on the stack. */
	while (*env++ != 0)	/* Skip over environment, and NULL terminator */
		;
	aux = (const Elf_Auxinfo *)env;

	/* Digest the auxiliary vector. */
	for (;  aux->a_type != AT_NULL; aux++) {
		switch (aux->a_type) {
		case AT_HWCAP:
			cpu_features = (uint32_t)aux->a_un.a_val;
			break;
		case AT_HWCAP2:
			cpu_features2 = (uint32_t)aux->a_un.a_val;
			break;
		}
	}
}