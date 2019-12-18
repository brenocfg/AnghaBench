#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct module {scalar_t__ ctfdata; scalar_t__ symtbl; scalar_t__ strings; TYPE_2__* strhdr; TYPE_1__* symhdr; int /*<<< orphan*/  ctfsize; } ;
struct TYPE_14__ {char* cts_name; scalar_t__ cts_data; int cts_entsize; scalar_t__ cts_offset; int /*<<< orphan*/  cts_size; scalar_t__ cts_flags; int /*<<< orphan*/  cts_type; } ;
typedef  TYPE_4__ ctf_sect_t ;
struct TYPE_13__ {int /*<<< orphan*/  cts_size; scalar_t__ cts_data; } ;
struct TYPE_15__ {int /*<<< orphan*/  ctf_size; TYPE_3__ ctf_data; scalar_t__ ctf_base; } ;
typedef  TYPE_5__ ctf_file_t ;
typedef  scalar_t__ caddr_t ;
struct TYPE_12__ {int /*<<< orphan*/  sh_size; } ;
struct TYPE_11__ {int /*<<< orphan*/  sh_size; } ;
typedef  int /*<<< orphan*/  Elf64_Sym ;
typedef  int /*<<< orphan*/  Elf32_Sym ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 scalar_t__ SHF_ALLOC ; 
 int /*<<< orphan*/  SHT_PROGBITS ; 
 int /*<<< orphan*/  SHT_STRTAB ; 
 int /*<<< orphan*/  SHT_SYMTAB ; 
 TYPE_5__* ctf_bufopen (TYPE_4__*,TYPE_4__*,TYPE_4__*,int*) ; 
 int /*<<< orphan*/  ctf_leave_compressed ; 
 int /*<<< orphan*/  kobj_set_ctf (struct module*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_lock ; 

ctf_file_t *
ctf_modopen(struct module *mp, int *error)
{
	ctf_sect_t ctfsect, symsect, strsect;
	ctf_file_t *fp = NULL;
	int err;

	if (error == NULL)
		error = &err;

	ctfsect.cts_name = ".SUNW_ctf";
	ctfsect.cts_type = SHT_PROGBITS;
	ctfsect.cts_flags = SHF_ALLOC;
	ctfsect.cts_data = mp->ctfdata;
	ctfsect.cts_size = mp->ctfsize;
	ctfsect.cts_entsize = 1;
	ctfsect.cts_offset = 0;

	symsect.cts_name = ".symtab";
	symsect.cts_type = SHT_SYMTAB;
	symsect.cts_flags = 0;
	symsect.cts_data = mp->symtbl;
	symsect.cts_size = mp->symhdr->sh_size;
#ifdef _LP64
	symsect.cts_entsize = sizeof (Elf64_Sym);
#else
	symsect.cts_entsize = sizeof (Elf32_Sym);
#endif
	symsect.cts_offset = 0;

	strsect.cts_name = ".strtab";
	strsect.cts_type = SHT_STRTAB;
	strsect.cts_flags = 0;
	strsect.cts_data = mp->strings;
	strsect.cts_size = mp->strhdr->sh_size;
	strsect.cts_entsize = 1;
	strsect.cts_offset = 0;

	ASSERT(MUTEX_HELD(&mod_lock));

	if ((fp = ctf_bufopen(&ctfsect, &symsect, &strsect, error)) == NULL)
		return (NULL);

	if (!ctf_leave_compressed && (caddr_t)fp->ctf_base != mp->ctfdata) {
		/*
		 * We must have just uncompressed the CTF data.  To avoid
		 * others having to pay the (substantial) cost of decompressing
		 * the data, we're going to substitute the uncompressed version
		 * for the compressed version.  Note that this implies that the
		 * first CTF consumer will induce memory impact on the system
		 * (but in the name of performance of future CTF consumers).
		 */
		kobj_set_ctf(mp, (caddr_t)fp->ctf_base, fp->ctf_size);
		fp->ctf_data.cts_data = fp->ctf_base;
		fp->ctf_data.cts_size = fp->ctf_size;
	}

	return (fp);
}