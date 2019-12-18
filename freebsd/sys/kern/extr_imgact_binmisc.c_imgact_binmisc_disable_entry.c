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
struct TYPE_3__ {int /*<<< orphan*/  ibe_flags; } ;
typedef  TYPE_1__ imgact_binmisc_entry_t ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  IBF_ENABLED ; 
 TYPE_1__* imgact_binmisc_find_entry (char*) ; 
 int /*<<< orphan*/  interp_list_sx ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
imgact_binmisc_disable_entry(char *name)
{
	imgact_binmisc_entry_t *ibe;

	sx_xlock(&interp_list_sx);
	if ((ibe = imgact_binmisc_find_entry(name)) == NULL) {
		sx_xunlock(&interp_list_sx);
		return (ENOENT);
	}

	ibe->ibe_flags &= ~IBF_ENABLED;
	sx_xunlock(&interp_list_sx);

	return (0);
}