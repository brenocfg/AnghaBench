#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  array_max; int /*<<< orphan*/  rel; int /*<<< orphan*/  old_type; int /*<<< orphan*/  old_prefix; } ;
struct TYPE_8__ {TYPE_1__ ty; } ;
struct TYPE_9__ {TYPE_2__ def; int /*<<< orphan*/  def_name; int /*<<< orphan*/  def_kind; } ;
typedef  TYPE_3__ definition ;
struct TYPE_10__ {int /*<<< orphan*/  array_max; int /*<<< orphan*/  rel; int /*<<< orphan*/  type; int /*<<< orphan*/  prefix; int /*<<< orphan*/  name; } ;
typedef  TYPE_4__ declaration ;

/* Variables and functions */
 int /*<<< orphan*/  DEF_TYPEDEF ; 
 int /*<<< orphan*/  check_type_name (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_declaration (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
def_typedef(definition *defp)
{
	declaration dec;

	defp->def_kind = DEF_TYPEDEF;
	get_declaration(&dec, DEF_TYPEDEF);
	defp->def_name = dec.name;
	check_type_name(dec.name, 1);
	defp->def.ty.old_prefix = dec.prefix;
	defp->def.ty.old_type = dec.type;
	defp->def.ty.rel = dec.rel;
	defp->def.ty.array_max = dec.array_max;
}