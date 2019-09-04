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
struct tempfile {int active; int /*<<< orphan*/  owner; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getpid () ; 
 scalar_t__ is_tempfile_active (struct tempfile*) ; 
 int /*<<< orphan*/  remove_tempfiles_on_exit ; 
 int /*<<< orphan*/  remove_tempfiles_on_signal ; 
 int /*<<< orphan*/  sigchain_push_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tempfile_list ; 
 int /*<<< orphan*/  volatile_list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void activate_tempfile(struct tempfile *tempfile)
{
	static int initialized;

	if (is_tempfile_active(tempfile))
		BUG("activate_tempfile called for active object");

	if (!initialized) {
		sigchain_push_common(remove_tempfiles_on_signal);
		atexit(remove_tempfiles_on_exit);
		initialized = 1;
	}

	volatile_list_add(&tempfile->list, &tempfile_list);
	tempfile->owner = getpid();
	tempfile->active = 1;
}