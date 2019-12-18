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
struct TYPE_5__ {int /*<<< orphan*/ * old_prefix; } ;
struct TYPE_6__ {TYPE_1__ ty; } ;
struct TYPE_7__ {scalar_t__ def_kind; int /*<<< orphan*/  def_name; TYPE_2__ def; } ;
typedef  TYPE_3__ definition ;

/* Variables and functions */
 scalar_t__ DEF_TYPEDEF ; 
 int streq (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int
typedefed(definition *def, const char *type)
{
	if (def->def_kind != DEF_TYPEDEF || def->def.ty.old_prefix != NULL) {
		return (0);
	} else {
		return (streq(def->def_name, type));
	}
}