#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int def_kind; } ;
typedef  TYPE_1__ definition ;

/* Variables and functions */
#define  DEF_PROGRAM 128 
 int /*<<< orphan*/  f_print (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fout ; 
 int /*<<< orphan*/  pprogramdef (TYPE_1__*,int) ; 

void
print_funcdef(definition *def, int headeronly)
{
	switch (def->def_kind) {
	case DEF_PROGRAM:
		f_print(fout, "\n");
		pprogramdef(def, headeronly);
		break;
	default:
		break;
	}
}