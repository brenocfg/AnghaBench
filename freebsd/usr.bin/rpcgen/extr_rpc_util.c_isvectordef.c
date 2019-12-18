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
typedef  int relation ;
struct TYPE_4__ {char* old_type; int rel; } ;
struct TYPE_5__ {TYPE_1__ ty; } ;
struct TYPE_6__ {TYPE_2__ def; } ;
typedef  TYPE_3__ definition ;

/* Variables and functions */
 scalar_t__ FINDVAL (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
#define  REL_ALIAS 131 
#define  REL_ARRAY 130 
#define  REL_POINTER 129 
#define  REL_VECTOR 128 
 int /*<<< orphan*/  defined ; 
 int /*<<< orphan*/  streq (char const*,char*) ; 
 int /*<<< orphan*/  typedefed ; 

int
isvectordef(const char *type, relation rel)
{
	definition *def;

	for (;;) {
		switch (rel) {
		case REL_VECTOR:
			return (!streq(type, "string"));
		case REL_ARRAY:
			return (0);
		case REL_POINTER:
			return (0);
		case REL_ALIAS:
			def = (definition *) FINDVAL(defined, type, typedefed);
			if (def == NULL) {
				return (0);
			}
			type = def->def.ty.old_type;
			rel = def->def.ty.rel;
		}
	}

	return (0);
}