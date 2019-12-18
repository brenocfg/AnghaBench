#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  XmapVal ;
struct TYPE_5__ {int type; int /*<<< orphan*/  fun; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ CStr ;

/* Variables and functions */
 int A_K_NKEYS ; 
 scalar_t__ Strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* arrow ; 

int
SetArrowKeys(const CStr *name, XmapVal *fun, int type)
{
    int i;
    for (i = 0; i < A_K_NKEYS; i++)
	if (Strcmp(name->buf, arrow[i].name) == 0) {
	    arrow[i].fun  = *fun;
	    arrow[i].type = type;
	    return 0;
	}
    return -1;
}