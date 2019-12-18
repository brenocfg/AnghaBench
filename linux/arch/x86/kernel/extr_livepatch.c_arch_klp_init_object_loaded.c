#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct klp_patch {TYPE_1__* mod; } ;
struct klp_object {char* name; } ;
struct TYPE_5__ {int e_shnum; } ;
struct klp_modinfo {scalar_t__ secstrings; TYPE_2__ hdr; TYPE_3__* sechdrs; } ;
struct TYPE_6__ {int sh_size; scalar_t__ sh_addr; scalar_t__ sh_name; } ;
struct TYPE_4__ {struct klp_modinfo* klp_info; } ;
typedef  TYPE_3__ Elf_Shdr ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int KSYM_NAME_LEN ; 
 int MODULE_NAME_LEN ; 
 int /*<<< orphan*/  apply_alternatives (void*,void*) ; 
 int /*<<< orphan*/  apply_paravirt (void*,void*) ; 
 int sscanf (scalar_t__,char*,char*,char*) ; 
 scalar_t__ strcmp (char*,char const*) ; 

void arch_klp_init_object_loaded(struct klp_patch *patch,
				 struct klp_object *obj)
{
	int cnt;
	struct klp_modinfo *info;
	Elf_Shdr *s, *alt = NULL, *para = NULL;
	void *aseg, *pseg;
	const char *objname;
	char sec_objname[MODULE_NAME_LEN];
	char secname[KSYM_NAME_LEN];

	info = patch->mod->klp_info;
	objname = obj->name ? obj->name : "vmlinux";

	/* See livepatch core code for BUILD_BUG_ON() explanation */
	BUILD_BUG_ON(MODULE_NAME_LEN < 56 || KSYM_NAME_LEN != 128);

	for (s = info->sechdrs; s < info->sechdrs + info->hdr.e_shnum; s++) {
		/* Apply per-object .klp.arch sections */
		cnt = sscanf(info->secstrings + s->sh_name,
			     ".klp.arch.%55[^.].%127s",
			     sec_objname, secname);
		if (cnt != 2)
			continue;
		if (strcmp(sec_objname, objname))
			continue;
		if (!strcmp(".altinstructions", secname))
			alt = s;
		if (!strcmp(".parainstructions", secname))
			para = s;
	}

	if (alt) {
		aseg = (void *) alt->sh_addr;
		apply_alternatives(aseg, aseg + alt->sh_size);
	}

	if (para) {
		pseg = (void *) para->sh_addr;
		apply_paravirt(pseg, pseg + para->sh_size);
	}
}