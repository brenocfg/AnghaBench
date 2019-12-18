#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ def_kind; int /*<<< orphan*/  def_name; } ;
typedef  TYPE_1__ definition ;

/* Variables and functions */
 scalar_t__ DEF_CONST ; 
 scalar_t__ DEF_PROGRAM ; 
 int streq (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int
findtype(definition *def, const char *type)
{

	if (def->def_kind == DEF_PROGRAM || def->def_kind == DEF_CONST) {
		return (0);
	} else {
		return (streq(def->def_name, type));
	}
}