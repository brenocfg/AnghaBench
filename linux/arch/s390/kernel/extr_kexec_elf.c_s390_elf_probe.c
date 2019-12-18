#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  e_ident; } ;
typedef  TYPE_1__ Elf_Ehdr ;

/* Variables and functions */
 int /*<<< orphan*/  ELFMAG ; 
 int ENOEXEC ; 
 int /*<<< orphan*/  SELFMAG ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s390_elf_probe(const char *buf, unsigned long len)
{
	const Elf_Ehdr *ehdr;

	if (len < sizeof(Elf_Ehdr))
		return -ENOEXEC;

	ehdr = (Elf_Ehdr *)buf;

	/* Only check the ELF magic number here and do proper validity check
	 * in the loader. Any check here that fails would send the erroneous
	 * ELF file to the image loader that does not care what it gets.
	 * (Most likely) causing behavior not intended by the user.
	 */
	if (memcmp(ehdr->e_ident, ELFMAG, SELFMAG) != 0)
		return -ENOEXEC;

	return 0;
}