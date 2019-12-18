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
struct TYPE_5__ {scalar_t__ type; int /*<<< orphan*/  fun; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {scalar_t__ len; int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ CStr ;

/* Variables and functions */
 int A_K_NKEYS ; 
 scalar_t__ Strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ XK_NOD ; 
 TYPE_2__* arrow ; 
 int /*<<< orphan*/  printOne (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 

void
PrintArrowKeys(const CStr *name)
{
    int i;

    for (i = 0; i < A_K_NKEYS; i++)
	if (name->len == 0 || Strcmp(name->buf, arrow[i].name) == 0)
	    if (arrow[i].type != XK_NOD)
		printOne(arrow[i].name, &arrow[i].fun, arrow[i].type);
}