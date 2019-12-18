#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ st_value; int /*<<< orphan*/  st_info; } ;
struct TYPE_9__ {scalar_t__ relocbase; } ;
struct TYPE_8__ {TYPE_5__* sym_out; TYPE_4__* defobj_out; int /*<<< orphan*/ * lockstate; } ;
typedef  TYPE_1__ SymLook ;
typedef  int /*<<< orphan*/  RtldLockState ;
typedef  int /*<<< orphan*/  DoneList ;

/* Variables and functions */
 scalar_t__ ELF_ST_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ STT_FUNC ; 
 scalar_t__ STT_GNU_IFUNC ; 
 int /*<<< orphan*/  donelist_init (int /*<<< orphan*/ *) ; 
 scalar_t__ make_function_pointer (TYPE_5__*,TYPE_4__*) ; 
 scalar_t__ rtld_resolve_ifunc (TYPE_4__*,TYPE_5__*) ; 
 scalar_t__ symlook_global (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  symlook_init (TYPE_1__*,char const*) ; 

__attribute__((used)) static const void **
get_program_var_addr(const char *name, RtldLockState *lockstate)
{
    SymLook req;
    DoneList donelist;

    symlook_init(&req, name);
    req.lockstate = lockstate;
    donelist_init(&donelist);
    if (symlook_global(&req, &donelist) != 0)
	return (NULL);
    if (ELF_ST_TYPE(req.sym_out->st_info) == STT_FUNC)
	return ((const void **)make_function_pointer(req.sym_out,
	  req.defobj_out));
    else if (ELF_ST_TYPE(req.sym_out->st_info) == STT_GNU_IFUNC)
	return ((const void **)rtld_resolve_ifunc(req.defobj_out, req.sym_out));
    else
	return ((const void **)(req.defobj_out->relocbase +
	  req.sym_out->st_value));
}