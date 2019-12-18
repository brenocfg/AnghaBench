#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_4__* decls; } ;
struct TYPE_11__ {TYPE_1__ st; } ;
struct TYPE_12__ {TYPE_2__ def; } ;
typedef  TYPE_3__ definition ;
struct TYPE_15__ {scalar_t__ rel; int /*<<< orphan*/  type; int /*<<< orphan*/ * prefix; } ;
struct TYPE_13__ {TYPE_6__ decl; struct TYPE_13__* next; } ;
typedef  TYPE_4__ decl_list ;
struct TYPE_14__ {scalar_t__ length; } ;
typedef  TYPE_5__ bas_type ;

/* Variables and functions */
 int GET ; 
 int PUT ; 
 scalar_t__ REL_ALIAS ; 
 scalar_t__ REL_VECTOR ; 
 int /*<<< orphan*/  f_print (int /*<<< orphan*/ ,char*) ; 
 TYPE_5__* find_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fout ; 
 int inline_size ; 
 int /*<<< orphan*/  inline_struct (TYPE_3__*,int) ; 
 int /*<<< orphan*/  print_stat (int,TYPE_6__*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
emit_struct(definition *def)
{
	decl_list *dl;
	int j, size, flag;
	bas_type *ptr;
	int can_inline;

	if (inline_size == 0) {
		/* No xdr_inlining at all */
		for (dl = def->def.st.decls; dl != NULL; dl = dl->next)
			print_stat(1, &dl->decl);
		return;
	}

	for (dl = def->def.st.decls; dl != NULL; dl = dl->next)
		if (dl->decl.rel == REL_VECTOR &&
		    strcmp(dl->decl.type, "opaque") != 0){
			f_print(fout, "\tint i;\n");
			break;
		}

	size = 0;
	can_inline = 0;
	/*
	 * Make a first pass and see if inling is possible.
	 */
	for (dl = def->def.st.decls; dl != NULL; dl = dl->next)
		if ((dl->decl.prefix == NULL) &&
		    ((ptr = find_type(dl->decl.type)) != NULL) &&
		    ((dl->decl.rel == REL_ALIAS)||
		     (dl->decl.rel == REL_VECTOR))){
			if (dl->decl.rel == REL_ALIAS)
				size += ptr->length;
			else {
				can_inline = 1;
				break; /* can be inlined */
			}
		} else {
			if (size >= inline_size){
				can_inline = 1;
				break; /* can be inlined */
			}
			size = 0;
		}
	if (size >= inline_size)
		can_inline = 1;

	if (can_inline == 0){	/* can not inline, drop back to old mode */
		for (dl = def->def.st.decls; dl != NULL; dl = dl->next)
			print_stat(1, &dl->decl);
		return;
	}

	flag = PUT;
	for (j = 0; j < 2; j++){
		inline_struct(def, flag);
		if (flag == PUT)
			flag = GET;
	}

	f_print(fout, "\t\treturn (TRUE);\n\t}\n\n");

	/* now take care of XDR_FREE case */

	for (dl = def->def.st.decls; dl != NULL; dl = dl->next)
		print_stat(1, &dl->decl);

}