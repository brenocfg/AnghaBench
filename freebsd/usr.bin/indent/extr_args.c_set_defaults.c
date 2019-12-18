#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pro {scalar_t__ p_type; int /*<<< orphan*/  p_default; int /*<<< orphan*/ * p_obj; scalar_t__ p_name; } ;
struct TYPE_2__ {double case_indent; } ;

/* Variables and functions */
 scalar_t__ PRO_SPECIAL ; 
 TYPE_1__ opt ; 
 struct pro* pro ; 

void
set_defaults(void)
{
    struct pro *p;

    /*
     * Because ps.case_indent is a float, we can't initialize it from the
     * table:
     */
    opt.case_indent = 0.0;	/* -cli0.0 */
    for (p = pro; p->p_name; p++)
	if (p->p_type != PRO_SPECIAL)
	    *p->p_obj = p->p_default;
}