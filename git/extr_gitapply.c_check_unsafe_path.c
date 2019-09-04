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
struct patch {char* old_name; char* new_name; int /*<<< orphan*/  new_mode; int /*<<< orphan*/  old_mode; scalar_t__ is_delete; int /*<<< orphan*/  is_copy; int /*<<< orphan*/  is_new; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int error (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  verify_path (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_unsafe_path(struct patch *patch)
{
	const char *old_name = NULL;
	const char *new_name = NULL;
	if (patch->is_delete)
		old_name = patch->old_name;
	else if (!patch->is_new && !patch->is_copy)
		old_name = patch->old_name;
	if (!patch->is_delete)
		new_name = patch->new_name;

	if (old_name && !verify_path(old_name, patch->old_mode))
		return error(_("invalid path '%s'"), old_name);
	if (new_name && !verify_path(new_name, patch->new_mode))
		return error(_("invalid path '%s'"), new_name);
	return 0;
}