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
struct TYPE_4__ {int rel; char* old_type; } ;
struct TYPE_5__ {TYPE_1__ ty; } ;
struct TYPE_6__ {scalar_t__ def_kind; TYPE_2__ def; } ;
typedef  TYPE_3__ definition ;

/* Variables and functions */
 scalar_t__ DEF_TYPEDEF ; 
 scalar_t__ FINDVAL (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
#define  REL_ALIAS 129 
#define  REL_VECTOR 128 
 int /*<<< orphan*/  defined ; 
 int /*<<< orphan*/  findit ; 
 int /*<<< orphan*/  streq (char*,char*) ; 

__attribute__((used)) static const char *
fixit(const char *type, const char *orig)
{
	definition *def;

	def = (definition *) FINDVAL(defined, type, findit);
	if (def == NULL || def->def_kind != DEF_TYPEDEF) {
		return (orig);
	}
	switch (def->def.ty.rel) {
	case REL_VECTOR:
		if (streq(def->def.ty.old_type, "opaque"))
			return ("char");
		else
			return (def->def.ty.old_type);

	case REL_ALIAS:
		return (fixit(def->def.ty.old_type, orig));
	default:
		return (orig);
	}
}