#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct plugin2 {scalar_t__ dsohandle; int /*<<< orphan*/  names; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  dlclose (scalar_t__) ; 
 int /*<<< orphan*/  heim_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
plug_dealloc(void *ptr)
{
    struct plugin2 *p = ptr;
    heim_release(p->path);
    heim_release(p->names);
    if (p->dsohandle)
	dlclose(p->dsohandle);
}