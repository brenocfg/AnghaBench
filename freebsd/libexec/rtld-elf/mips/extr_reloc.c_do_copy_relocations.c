#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  r_info; scalar_t__ r_offset; } ;
struct TYPE_14__ {int st_name; size_t st_size; scalar_t__ st_value; } ;
struct TYPE_13__ {int relsize; char* strtab; scalar_t__ relocbase; int /*<<< orphan*/  path; TYPE_3__* symtab; TYPE_4__* rel; int /*<<< orphan*/  mainprog; } ;
struct TYPE_12__ {TYPE_2__ const* defobj_out; TYPE_3__* sym_out; int /*<<< orphan*/  flags; int /*<<< orphan*/  ventry; } ;
typedef  TYPE_1__ SymLook ;
typedef  TYPE_2__ const Obj_Entry ;
typedef  TYPE_3__ Elf_Sym ;
typedef  TYPE_4__ Elf_Rel ;

/* Variables and functions */
 int ELF_R_SYM (int /*<<< orphan*/ ) ; 
 scalar_t__ ELF_R_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ R_MIPS_COPY ; 
 int /*<<< orphan*/  SYMLOOK_EARLY ; 
 int /*<<< orphan*/  _rtld_error (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fetch_ventry (TYPE_2__ const*,int) ; 
 TYPE_2__ const* globallist_next (TYPE_2__ const*) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,size_t) ; 
 int /*<<< orphan*/  symlook_init (TYPE_1__*,char const*) ; 
 int symlook_obj (TYPE_1__*,TYPE_2__ const*) ; 

int
do_copy_relocations(Obj_Entry *dstobj)
{
	const Obj_Entry *srcobj, *defobj;
	const Elf_Rel *rellim;
	const Elf_Rel *rel;
	const Elf_Sym *srcsym;
	const Elf_Sym *dstsym;
	const void *srcaddr;
	const char *name;
	void *dstaddr;
	SymLook req;
	size_t size;
	int res;

	/*
	 * COPY relocs are invalid outside of the main program
	 */
	assert(dstobj->mainprog);

	rellim = (const Elf_Rel *)((const char *)dstobj->rel + dstobj->relsize);
	for (rel = dstobj->rel; rel < rellim; rel++) {
		if (ELF_R_TYPE(rel->r_info) != R_MIPS_COPY)
			continue;

		dstaddr = (void *)(dstobj->relocbase + rel->r_offset);
		dstsym = dstobj->symtab + ELF_R_SYM(rel->r_info);
		name = dstobj->strtab + dstsym->st_name;
		size = dstsym->st_size;

		symlook_init(&req, name);
		req.ventry = fetch_ventry(dstobj, ELF_R_SYM(rel->r_info));
		req.flags = SYMLOOK_EARLY;

		for (srcobj = globallist_next(dstobj); srcobj != NULL;
		     srcobj = globallist_next(srcobj)) {
			res = symlook_obj(&req, srcobj);
			if (res == 0) {
				srcsym = req.sym_out;
				defobj = req.defobj_out;
				break;
			}
		}
		if (srcobj == NULL) {
			_rtld_error(
"Undefined symbol \"%s\" referenced from COPY relocation in %s",
			    name, dstobj->path);
			return (-1);
		}

		srcaddr = (const void *)(defobj->relocbase + srcsym->st_value);
		memcpy(dstaddr, srcaddr, size);
	}

	return (0);
}