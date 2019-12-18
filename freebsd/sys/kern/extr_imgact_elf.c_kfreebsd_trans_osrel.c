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
typedef  int int32_t ;
struct TYPE_3__ {int /*<<< orphan*/  n_namesz; } ;
typedef  TYPE_1__ Elf_Note ;
typedef  int Elf32_Word ;

/* Variables and functions */
 int /*<<< orphan*/  ELF_NOTE_ROUNDSIZE ; 
 int const GNU_KFREEBSD_ABI_DESC ; 
 scalar_t__ roundup2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
kfreebsd_trans_osrel(const Elf_Note *note, int32_t *osrel)
{
	const Elf32_Word *desc;
	uintptr_t p;

	p = (uintptr_t)(note + 1);
	p += roundup2(note->n_namesz, ELF_NOTE_ROUNDSIZE);

	desc = (const Elf32_Word *)p;
	if (desc[0] != GNU_KFREEBSD_ABI_DESC)
		return (false);

	/*
	 * Debian GNU/kFreeBSD embed the earliest compatible kernel version
	 * (__FreeBSD_version: <major><two digit minor>Rxx) in the LSB way.
	 */
	*osrel = desc[1] * 100000 + desc[2] * 1000 + desc[3];

	return (true);
}