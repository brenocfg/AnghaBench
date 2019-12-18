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
typedef  int /*<<< orphan*/  dtrace_id_t ;
struct TYPE_3__ {char* dtargd_native; int /*<<< orphan*/  dtargd_ndx; } ;
typedef  TYPE_1__ dtrace_argdesc_t ;

/* Variables and functions */
 int /*<<< orphan*/  DTRACE_ARGNONE ; 
 scalar_t__ SYSTRACE_ISENTRY (uintptr_t) ; 
 int SYSTRACE_SYSNUM (uintptr_t) ; 
 int /*<<< orphan*/  systrace_entry_setargdesc (int,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  systrace_return_setargdesc (int,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
systrace_getargdesc(void *arg, dtrace_id_t id, void *parg,
    dtrace_argdesc_t *desc)
{
	int sysnum = SYSTRACE_SYSNUM((uintptr_t)parg);

	if (SYSTRACE_ISENTRY((uintptr_t)parg))
		systrace_entry_setargdesc(sysnum, desc->dtargd_ndx,
		    desc->dtargd_native, sizeof(desc->dtargd_native));
	else
		systrace_return_setargdesc(sysnum, desc->dtargd_ndx,
		    desc->dtargd_native, sizeof(desc->dtargd_native));

	if (desc->dtargd_native[0] == '\0')
		desc->dtargd_ndx = DTRACE_ARGNONE;
}