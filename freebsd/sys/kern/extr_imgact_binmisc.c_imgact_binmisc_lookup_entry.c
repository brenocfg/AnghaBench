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
typedef  int /*<<< orphan*/  ximgact_binmisc_entry_t ;
typedef  int /*<<< orphan*/  imgact_binmisc_entry_t ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/ * imgact_binmisc_find_entry (char*) ; 
 int imgact_binmisc_populate_xbe (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  interp_list_sx ; 
 int /*<<< orphan*/  sx_slock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_sunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
imgact_binmisc_lookup_entry(char *name, ximgact_binmisc_entry_t *xbe)
{
	imgact_binmisc_entry_t *ibe;
	int error = 0;

	sx_slock(&interp_list_sx);
	if ((ibe = imgact_binmisc_find_entry(name)) == NULL) {
		sx_sunlock(&interp_list_sx);
		return (ENOENT);
	}

	error = imgact_binmisc_populate_xbe(xbe, ibe);
	sx_sunlock(&interp_list_sx);

	return (error);
}