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
struct kpwd_proc {int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 struct kpwd_proc* procs ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static struct kpwd_proc *
find_chpw_proto(const char *name)
{
    struct kpwd_proc *p;
    for (p = procs; p->name != NULL; p++) {
	if (strcmp(p->name, name) == 0)
	    return p;
    }
    return NULL;
}