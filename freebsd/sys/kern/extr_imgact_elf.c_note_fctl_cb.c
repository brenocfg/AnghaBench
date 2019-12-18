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
struct fctl_cb_arg {int /*<<< orphan*/ * fctl0; } ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_3__ {int /*<<< orphan*/  n_namesz; } ;
typedef  TYPE_1__ Elf_Note ;
typedef  int /*<<< orphan*/  Elf32_Word ;

/* Variables and functions */
 int /*<<< orphan*/  ELF_NOTE_ROUNDSIZE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ roundup2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static boolean_t
note_fctl_cb(const Elf_Note *note, void *arg0, boolean_t *res)
{
	struct fctl_cb_arg *arg;
	const Elf32_Word *desc;
	uintptr_t p;

	arg = arg0;
	p = (uintptr_t)(note + 1);
	p += roundup2(note->n_namesz, ELF_NOTE_ROUNDSIZE);
	desc = (const Elf32_Word *)p;
	*arg->fctl0 = desc[0];
	return (TRUE);
}