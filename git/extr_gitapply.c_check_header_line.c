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
struct patch {int is_delete; int is_new; int is_rename; int is_copy; char* extension_linenr; } ;
struct apply_state {char* linenr; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int error (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int check_header_line(struct apply_state *state, struct patch *patch)
{
	int extensions = (patch->is_delete == 1) + (patch->is_new == 1) +
			 (patch->is_rename == 1) + (patch->is_copy == 1);
	if (extensions > 1)
		return error(_("inconsistent header lines %d and %d"),
			     patch->extension_linenr, state->linenr);
	if (extensions && !patch->extension_linenr)
		patch->extension_linenr = state->linenr;
	return 0;
}