#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  path; } ;
struct TYPE_17__ {int st_name; int /*<<< orphan*/  st_info; int /*<<< orphan*/  st_shndx; int /*<<< orphan*/  st_value; } ;
struct TYPE_16__ {char* strtab; int* versyms; size_t vernum; TYPE_1__* vertab; int /*<<< orphan*/  path; TYPE_6__* symtab; } ;
struct TYPE_15__ {int flags; char const* name; TYPE_2__* ventry; } ;
struct TYPE_14__ {TYPE_6__ const* sym_out; int /*<<< orphan*/  vcount; TYPE_6__ const* vsymp; } ;
struct TYPE_13__ {char const* name; scalar_t__ hash; } ;
struct TYPE_12__ {scalar_t__ hash; char const* name; } ;
typedef  TYPE_3__ Sym_Match_Result ;
typedef  TYPE_4__ SymLook ;
typedef  TYPE_5__ Obj_Entry ;
typedef  size_t Elf_Versym ;
typedef  TYPE_6__ Elf_Sym ;

/* Variables and functions */
 int const ELF_ST_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHN_UNDEF ; 
#define  STT_COMMON 133 
#define  STT_FUNC 132 
#define  STT_GNU_IFUNC 131 
#define  STT_NOTYPE 130 
#define  STT_OBJECT 129 
#define  STT_TLS 128 
 int SYMLOOK_DLSYM ; 
 int SYMLOOK_IN_PLT ; 
 size_t VER_NDX (int) ; 
 size_t VER_NDX_GIVEN ; 
 int VER_NDX_HIDDEN ; 
 int /*<<< orphan*/  _rtld_error (char*,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_8__ obj_rtld ; 
 scalar_t__ object_match_name (TYPE_5__ const*,char const*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static bool
matched_symbol(SymLook *req, const Obj_Entry *obj, Sym_Match_Result *result,
    const unsigned long symnum)
{
	Elf_Versym verndx;
	const Elf_Sym *symp;
	const char *strp;

	symp = obj->symtab + symnum;
	strp = obj->strtab + symp->st_name;

	switch (ELF_ST_TYPE(symp->st_info)) {
	case STT_FUNC:
	case STT_NOTYPE:
	case STT_OBJECT:
	case STT_COMMON:
	case STT_GNU_IFUNC:
		if (symp->st_value == 0)
			return (false);
		/* fallthrough */
	case STT_TLS:
		if (symp->st_shndx != SHN_UNDEF)
			break;
#ifndef __mips__
		else if (((req->flags & SYMLOOK_IN_PLT) == 0) &&
		    (ELF_ST_TYPE(symp->st_info) == STT_FUNC))
			break;
#endif
		/* fallthrough */
	default:
		return (false);
	}
	if (req->name[0] != strp[0] || strcmp(req->name, strp) != 0)
		return (false);

	if (req->ventry == NULL) {
		if (obj->versyms != NULL) {
			verndx = VER_NDX(obj->versyms[symnum]);
			if (verndx > obj->vernum) {
				_rtld_error(
				    "%s: symbol %s references wrong version %d",
				    obj->path, obj->strtab + symnum, verndx);
				return (false);
			}
			/*
			 * If we are not called from dlsym (i.e. this
			 * is a normal relocation from unversioned
			 * binary), accept the symbol immediately if
			 * it happens to have first version after this
			 * shared object became versioned.  Otherwise,
			 * if symbol is versioned and not hidden,
			 * remember it. If it is the only symbol with
			 * this name exported by the shared object, it
			 * will be returned as a match by the calling
			 * function. If symbol is global (verndx < 2)
			 * accept it unconditionally.
			 */
			if ((req->flags & SYMLOOK_DLSYM) == 0 &&
			    verndx == VER_NDX_GIVEN) {
				result->sym_out = symp;
				return (true);
			}
			else if (verndx >= VER_NDX_GIVEN) {
				if ((obj->versyms[symnum] & VER_NDX_HIDDEN)
				    == 0) {
					if (result->vsymp == NULL)
						result->vsymp = symp;
					result->vcount++;
				}
				return (false);
			}
		}
		result->sym_out = symp;
		return (true);
	}
	if (obj->versyms == NULL) {
		if (object_match_name(obj, req->ventry->name)) {
			_rtld_error("%s: object %s should provide version %s "
			    "for symbol %s", obj_rtld.path, obj->path,
			    req->ventry->name, obj->strtab + symnum);
			return (false);
		}
	} else {
		verndx = VER_NDX(obj->versyms[symnum]);
		if (verndx > obj->vernum) {
			_rtld_error("%s: symbol %s references wrong version %d",
			    obj->path, obj->strtab + symnum, verndx);
			return (false);
		}
		if (obj->vertab[verndx].hash != req->ventry->hash ||
		    strcmp(obj->vertab[verndx].name, req->ventry->name)) {
			/*
			 * Version does not match. Look if this is a
			 * global symbol and if it is not hidden. If
			 * global symbol (verndx < 2) is available,
			 * use it. Do not return symbol if we are
			 * called by dlvsym, because dlvsym looks for
			 * a specific version and default one is not
			 * what dlvsym wants.
			 */
			if ((req->flags & SYMLOOK_DLSYM) ||
			    (verndx >= VER_NDX_GIVEN) ||
			    (obj->versyms[symnum] & VER_NDX_HIDDEN))
				return (false);
		}
	}
	result->sym_out = symp;
	return (true);
}