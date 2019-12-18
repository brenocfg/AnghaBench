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
typedef  int /*<<< orphan*/  relation ;
struct TYPE_6__ {char* old_prefix; char* old_type; char* array_max; int /*<<< orphan*/  rel; } ;
struct TYPE_5__ {TYPE_2__ ty; } ;
struct TYPE_7__ {int /*<<< orphan*/  def_name; TYPE_1__ def; } ;
typedef  TYPE_3__ definition ;

/* Variables and functions */
 int /*<<< orphan*/  print_ifstat (int,char const*,char const*,int /*<<< orphan*/ ,char const*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
emit_typedef(definition *def)
{
	const char *prefix = def->def.ty.old_prefix;
	const char *type = def->def.ty.old_type;
	const char *amax = def->def.ty.array_max;
	relation rel = def->def.ty.rel;

	print_ifstat(1, prefix, type, rel, amax, "objp", def->def_name);
}