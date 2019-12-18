#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {char* name; } ;
typedef  TYPE_1__ Ver_Entry ;
struct TYPE_22__ {int st_name; int /*<<< orphan*/  st_info; } ;
struct TYPE_21__ {unsigned long dynsymcount; char* strtab; int /*<<< orphan*/  path; TYPE_5__* symtab; } ;
struct TYPE_20__ {TYPE_4__ const* obj; TYPE_5__ const* sym; } ;
struct TYPE_19__ {int flags; TYPE_4__ const* defobj_out; TYPE_5__* sym_out; int /*<<< orphan*/ * lockstate; TYPE_1__* ventry; } ;
typedef  TYPE_2__ SymLook ;
typedef  TYPE_3__ SymCache ;
typedef  int /*<<< orphan*/  RtldLockState ;
typedef  TYPE_4__ const Obj_Entry ;
typedef  TYPE_5__ Elf_Sym ;

/* Variables and functions */
 scalar_t__ ELF_ST_BIND (int /*<<< orphan*/ ) ; 
 scalar_t__ ELF_ST_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ STB_LOCAL ; 
 scalar_t__ STB_WEAK ; 
 scalar_t__ STT_SECTION ; 
 int /*<<< orphan*/  _rtld_error (char*,int /*<<< orphan*/ ,...) ; 
 TYPE_1__* fetch_ventry (TYPE_4__ const*,unsigned long) ; 
 TYPE_4__ const* obj_main ; 
 TYPE_4__ const obj_rtld ; 
 TYPE_5__ sym_zero ; 
 int symlook_default (TYPE_2__*,TYPE_4__ const*) ; 
 int /*<<< orphan*/  symlook_init (TYPE_2__*,char const*) ; 

const Elf_Sym *
find_symdef(unsigned long symnum, const Obj_Entry *refobj,
    const Obj_Entry **defobj_out, int flags, SymCache *cache,
    RtldLockState *lockstate)
{
    const Elf_Sym *ref;
    const Elf_Sym *def;
    const Obj_Entry *defobj;
    const Ver_Entry *ve;
    SymLook req;
    const char *name;
    int res;

    /*
     * If we have already found this symbol, get the information from
     * the cache.
     */
    if (symnum >= refobj->dynsymcount)
	return NULL;	/* Bad object */
    if (cache != NULL && cache[symnum].sym != NULL) {
	*defobj_out = cache[symnum].obj;
	return cache[symnum].sym;
    }

    ref = refobj->symtab + symnum;
    name = refobj->strtab + ref->st_name;
    def = NULL;
    defobj = NULL;
    ve = NULL;

    /*
     * We don't have to do a full scale lookup if the symbol is local.
     * We know it will bind to the instance in this load module; to
     * which we already have a pointer (ie ref). By not doing a lookup,
     * we not only improve performance, but it also avoids unresolvable
     * symbols when local symbols are not in the hash table. This has
     * been seen with the ia64 toolchain.
     */
    if (ELF_ST_BIND(ref->st_info) != STB_LOCAL) {
	if (ELF_ST_TYPE(ref->st_info) == STT_SECTION) {
	    _rtld_error("%s: Bogus symbol table entry %lu", refobj->path,
		symnum);
	}
	symlook_init(&req, name);
	req.flags = flags;
	ve = req.ventry = fetch_ventry(refobj, symnum);
	req.lockstate = lockstate;
	res = symlook_default(&req, refobj);
	if (res == 0) {
	    def = req.sym_out;
	    defobj = req.defobj_out;
	}
    } else {
	def = ref;
	defobj = refobj;
    }

    /*
     * If we found no definition and the reference is weak, treat the
     * symbol as having the value zero.
     */
    if (def == NULL && ELF_ST_BIND(ref->st_info) == STB_WEAK) {
	def = &sym_zero;
	defobj = obj_main;
    }

    if (def != NULL) {
	*defobj_out = defobj;
	/* Record the information in the cache to avoid subsequent lookups. */
	if (cache != NULL) {
	    cache[symnum].sym = def;
	    cache[symnum].obj = defobj;
	}
    } else {
	if (refobj != &obj_rtld)
	    _rtld_error("%s: Undefined symbol \"%s%s%s\"", refobj->path, name,
	      ve != NULL ? "@" : "", ve != NULL ? ve->name : "");
    }
    return def;
}