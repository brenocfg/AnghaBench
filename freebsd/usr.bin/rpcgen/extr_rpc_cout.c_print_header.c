#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  rel; int /*<<< orphan*/  old_type; } ;
struct TYPE_6__ {TYPE_1__ ty; } ;
struct TYPE_7__ {scalar_t__ def_kind; TYPE_2__ def; int /*<<< orphan*/  def_name; } ;
typedef  TYPE_3__ definition ;

/* Variables and functions */
 scalar_t__ DEF_TYPEDEF ; 
 int /*<<< orphan*/  f_print (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fout ; 
 scalar_t__ inline_size ; 
 int /*<<< orphan*/  isvectordef (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_generic_header (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
print_header(definition *def)
{
	print_generic_header(def->def_name,
			    def->def_kind != DEF_TYPEDEF ||
			    !isvectordef(def->def.ty.old_type,
					 def->def.ty.rel));
	/* Now add Inline support */

	if (inline_size == 0)
		return;
	/* May cause lint to complain. but  ... */
	f_print(fout, "\tregister long *buf;\n\n");
}