#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int relocated; int /*<<< orphan*/  version; int /*<<< orphan*/  magic; int /*<<< orphan*/  mainprog; scalar_t__ bind_now; scalar_t__ textrel; int /*<<< orphan*/  path; scalar_t__ valid_hash_gnu; scalar_t__ valid_hash_sysv; int /*<<< orphan*/ * strtab; int /*<<< orphan*/ * symtab; } ;
typedef  int /*<<< orphan*/  RtldLockState ;
typedef  TYPE_1__ Obj_Entry ;

/* Variables and functions */
 int /*<<< orphan*/  RTLD_MAGIC ; 
 int /*<<< orphan*/  RTLD_VERSION ; 
 int /*<<< orphan*/  _rtld_error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_pltgot (TYPE_1__*) ; 
 int obj_enforce_relro (TYPE_1__*) ; 
 int reloc_jmpslots (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ reloc_non_plt (TYPE_1__*,TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int reloc_plt (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ reloc_textrel_prot (TYPE_1__*,int) ; 

__attribute__((used)) static int
relocate_object(Obj_Entry *obj, bool bind_now, Obj_Entry *rtldobj,
    int flags, RtldLockState *lockstate)
{

	if (obj->relocated)
		return (0);
	obj->relocated = true;
	if (obj != rtldobj)
		dbg("relocating \"%s\"", obj->path);

	if (obj->symtab == NULL || obj->strtab == NULL ||
	    !(obj->valid_hash_sysv || obj->valid_hash_gnu)) {
		_rtld_error("%s: Shared object has no run-time symbol table",
			    obj->path);
		return (-1);
	}

	/* There are relocations to the write-protected text segment. */
	if (obj->textrel && reloc_textrel_prot(obj, true) != 0)
		return (-1);

	/* Process the non-PLT non-IFUNC relocations. */
	if (reloc_non_plt(obj, rtldobj, flags, lockstate))
		return (-1);

	/* Re-protected the text segment. */
	if (obj->textrel && reloc_textrel_prot(obj, false) != 0)
		return (-1);

	/* Set the special PLT or GOT entries. */
	init_pltgot(obj);

	/* Process the PLT relocations. */
	if (reloc_plt(obj, flags, lockstate) == -1)
		return (-1);
	/* Relocate the jump slots if we are doing immediate binding. */
	if ((obj->bind_now || bind_now) && reloc_jmpslots(obj, flags,
	    lockstate) == -1)
		return (-1);

	if (!obj->mainprog && obj_enforce_relro(obj) == -1)
		return (-1);

	/*
	 * Set up the magic number and version in the Obj_Entry.  These
	 * were checked in the crt1.o from the original ElfKit, so we
	 * set them for backward compatibility.
	 */
	obj->magic = RTLD_MAGIC;
	obj->version = RTLD_VERSION;

	return (0);
}