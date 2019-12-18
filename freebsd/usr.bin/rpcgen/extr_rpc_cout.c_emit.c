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
struct TYPE_11__ {int /*<<< orphan*/  old_type; } ;
struct TYPE_12__ {TYPE_1__ ty; } ;
struct TYPE_13__ {int def_kind; int /*<<< orphan*/  def_name; TYPE_2__ def; } ;
typedef  TYPE_3__ definition ;

/* Variables and functions */
 int DEF_CONST ; 
#define  DEF_ENUM 131 
 int DEF_PROGRAM ; 
#define  DEF_STRUCT 130 
#define  DEF_TYPEDEF 129 
#define  DEF_UNION 128 
 int /*<<< orphan*/  emit_enum (TYPE_3__*) ; 
 int /*<<< orphan*/  emit_program (TYPE_3__*) ; 
 int /*<<< orphan*/  emit_struct (TYPE_3__*) ; 
 int /*<<< orphan*/  emit_typedef (TYPE_3__*) ; 
 int /*<<< orphan*/  emit_union (TYPE_3__*) ; 
 int /*<<< orphan*/  print_header (TYPE_3__*) ; 
 int /*<<< orphan*/  print_trailer () ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
emit(definition *def)
{
	if (def->def_kind == DEF_CONST) {
		return;
	}
	if (def->def_kind == DEF_PROGRAM) {
		emit_program(def);
		return;
	}
	if (def->def_kind == DEF_TYPEDEF) {
		/*
		 * now we need to handle declarations like
		 * struct typedef foo foo;
		 * since we dont want this to be expanded into 2 calls to xdr_foo
		 */

		if (strcmp(def->def.ty.old_type, def->def_name) == 0)
			return;
	}
	print_header(def);
	switch (def->def_kind) {
	case DEF_UNION:
		emit_union(def);
		break;
	case DEF_ENUM:
		emit_enum(def);
		break;
	case DEF_STRUCT:
		emit_struct(def);
		break;
	case DEF_TYPEDEF:
		emit_typedef(def);
		break;
		/* DEF_CONST and DEF_PROGRAM have already been handled */
	default:
		break;
	}
	print_trailer();
}