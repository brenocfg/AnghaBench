#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  rel; int /*<<< orphan*/  old_type; } ;
struct TYPE_12__ {TYPE_1__ ty; } ;
struct TYPE_13__ {int def_kind; TYPE_2__ def; int /*<<< orphan*/  def_name; } ;
typedef  TYPE_3__ definition ;

/* Variables and functions */
#define  DEF_CONST 133 
#define  DEF_ENUM 132 
#define  DEF_PROGRAM 131 
#define  DEF_STRUCT 130 
#define  DEF_TYPEDEF 129 
#define  DEF_UNION 128 
 int /*<<< orphan*/  f_print (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fout ; 
 int /*<<< orphan*/  isvectordef (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pconstdef (TYPE_3__*) ; 
 int /*<<< orphan*/  penumdef (TYPE_3__*) ; 
 int /*<<< orphan*/  pprogramdef (TYPE_3__*,int) ; 
 int /*<<< orphan*/  pstructdef (TYPE_3__*) ; 
 int /*<<< orphan*/  ptypedef (TYPE_3__*) ; 
 int /*<<< orphan*/  puniondef (TYPE_3__*) ; 
 int /*<<< orphan*/  storexdrfuncdecl (int /*<<< orphan*/ ,int) ; 

void
print_datadef(definition *def, int headeronly)
{

	if (def->def_kind == DEF_PROGRAM)  /* handle data only */
		return;

	if (def->def_kind != DEF_CONST) {
		f_print(fout, "\n");
	}
	switch (def->def_kind) {
	case DEF_STRUCT:
		pstructdef(def);
		break;
	case DEF_UNION:
		puniondef(def);
		break;
	case DEF_ENUM:
		penumdef(def);
		break;
	case DEF_TYPEDEF:
		ptypedef(def);
		break;
	case DEF_PROGRAM:
		pprogramdef(def, headeronly);
		break;
	case DEF_CONST:
		pconstdef(def);
		break;
	}
	if (def->def_kind != DEF_PROGRAM && def->def_kind != DEF_CONST) {
	    storexdrfuncdecl(def->def_name,
			     def->def_kind != DEF_TYPEDEF ||
			     !isvectordef(def->def.ty.old_type,
					  def->def.ty.rel));
	}
}