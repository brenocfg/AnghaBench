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
typedef  int /*<<< orphan*/  imgact_binmisc_entry_t ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  SLIST_REMOVE (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imgact_binmisc_destroy_entry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  imgact_binmisc_entry ; 
 int /*<<< orphan*/ * imgact_binmisc_find_entry (char*) ; 
 int /*<<< orphan*/  interp_list_entry_count ; 
 int /*<<< orphan*/  interp_list_sx ; 
 int /*<<< orphan*/  interpreter_list ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
imgact_binmisc_remove_entry(char *name)
{
	imgact_binmisc_entry_t *ibe;

	sx_xlock(&interp_list_sx);
	if ((ibe = imgact_binmisc_find_entry(name)) == NULL) {
		sx_xunlock(&interp_list_sx);
		return (ENOENT);
	}
	SLIST_REMOVE(&interpreter_list, ibe, imgact_binmisc_entry, link);
	interp_list_entry_count--;
	sx_xunlock(&interp_list_sx);

	imgact_binmisc_destroy_entry(ibe);

	return (0);
}