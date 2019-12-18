#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* e_ident; } ;
typedef  TYPE_1__ GElf_Ehdr ;
typedef  int /*<<< orphan*/  Elf ;

/* Variables and functions */
 size_t EI_CLASS ; 
 int ELFCLASSNONE ; 
 int /*<<< orphan*/  ELF_C_READ ; 
 int /*<<< orphan*/ * elf_begin (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gelf_getehdr (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int
getelfclass(int fd)
{
	GElf_Ehdr ehdr;
	Elf *e;
	int class;

	class = ELFCLASSNONE;

	if ((e = elf_begin(fd, ELF_C_READ, NULL)) == NULL)
		goto out;
	if (gelf_getehdr(e, &ehdr) == NULL)
		goto out;
	class = ehdr.e_ident[EI_CLASS];
out:
	(void)elf_end(e);
	return (class);
}