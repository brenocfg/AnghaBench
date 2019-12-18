#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  st_info; } ;
struct TYPE_12__ {TYPE_1__* obj; struct TYPE_12__* next; } ;
struct TYPE_11__ {int /*<<< orphan*/  const* defobj_out; TYPE_4__ const* sym_out; } ;
struct TYPE_10__ {int /*<<< orphan*/  dagmembers; } ;
typedef  TYPE_2__ SymLook ;
typedef  int /*<<< orphan*/  const Obj_Entry ;
typedef  TYPE_3__ Needed_Entry ;
typedef  TYPE_4__ const Elf_Sym ;
typedef  int /*<<< orphan*/  DoneList ;

/* Variables and functions */
 scalar_t__ ELF_ST_BIND (int /*<<< orphan*/ ) ; 
 int ESRCH ; 
 scalar_t__ STB_WEAK ; 
 int /*<<< orphan*/  symlook_init_from_req (TYPE_2__*,TYPE_2__*) ; 
 int symlook_list (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
symlook_needed(SymLook *req, const Needed_Entry *needed, DoneList *dlp)
{
    const Elf_Sym *def;
    const Needed_Entry *n;
    const Obj_Entry *defobj;
    SymLook req1;
    int res;

    def = NULL;
    defobj = NULL;
    symlook_init_from_req(&req1, req);
    for (n = needed; n != NULL; n = n->next) {
	if (n->obj == NULL ||
	    (res = symlook_list(&req1, &n->obj->dagmembers, dlp)) != 0)
	    continue;
	if (def == NULL || ELF_ST_BIND(req1.sym_out->st_info) != STB_WEAK) {
	    def = req1.sym_out;
	    defobj = req1.defobj_out;
	    if (ELF_ST_BIND(def->st_info) != STB_WEAK)
		break;
	}
    }
    if (def != NULL) {
	req->sym_out = def;
	req->defobj_out = defobj;
	return (0);
    }
    return (ESRCH);
}