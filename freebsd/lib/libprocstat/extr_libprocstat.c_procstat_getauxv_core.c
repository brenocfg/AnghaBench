#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct procstat_core {int dummy; } ;
typedef  int /*<<< orphan*/  Elf_Auxinfo ;

/* Variables and functions */
 int /*<<< orphan*/  PSC_TYPE_AUXV ; 
 int /*<<< orphan*/ * procstat_core_get (struct procstat_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*) ; 

__attribute__((used)) static Elf_Auxinfo *
procstat_getauxv_core(struct procstat_core *core, unsigned int *cntp)
{
	Elf_Auxinfo *auxv;
	size_t len;

	auxv = procstat_core_get(core, PSC_TYPE_AUXV, NULL, &len);
	if (auxv == NULL)
		return (NULL);
	*cntp = len / sizeof(Elf_Auxinfo);
	return (auxv);
}