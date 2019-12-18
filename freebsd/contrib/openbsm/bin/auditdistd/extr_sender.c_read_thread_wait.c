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
struct TYPE_2__ {int adh_reset; int /*<<< orphan*/  adh_directory; int /*<<< orphan*/  adh_trail_offset; int /*<<< orphan*/  adh_trail_name; int /*<<< orphan*/ * adh_remote; } ;

/* Variables and functions */
 TYPE_1__* adhost ; 
 int /*<<< orphan*/  adist_remote_cond ; 
 int /*<<< orphan*/  adist_remote_mtx ; 
 int /*<<< orphan*/  adist_trail ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pjdlog_debug (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trail_close (int /*<<< orphan*/ ) ; 
 int trail_filefd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trail_filename (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trail_next (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trail_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trail_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_dir () ; 
 int /*<<< orphan*/  wait_for_file_init (int) ; 

__attribute__((used)) static bool
read_thread_wait(void)
{
	bool newfile = false;

	mtx_lock(&adist_remote_mtx);
	if (adhost->adh_reset) {
reset:
		adhost->adh_reset = false;
		if (trail_filefd(adist_trail) != -1)
			trail_close(adist_trail);
		trail_reset(adist_trail);
		while (adhost->adh_remote == NULL)
			cv_wait(&adist_remote_cond, &adist_remote_mtx);
		trail_start(adist_trail, adhost->adh_trail_name,
		    adhost->adh_trail_offset);
		newfile = true;
	}
	mtx_unlock(&adist_remote_mtx);
	while (trail_filefd(adist_trail) == -1) {
		newfile = true;
		wait_for_dir();
		/*
		 * We may have been disconnected and reconnected in the
		 * meantime, check if reset is set.
		 */
		mtx_lock(&adist_remote_mtx);
		if (adhost->adh_reset)
			goto reset;
		mtx_unlock(&adist_remote_mtx);
		if (trail_filefd(adist_trail) == -1)
			trail_next(adist_trail);
	}
	if (newfile) {
		pjdlog_debug(1, "Trail file \"%s/%s\" opened.",
		    adhost->adh_directory,
		    trail_filename(adist_trail));
		(void)wait_for_file_init(trail_filefd(adist_trail));
	}
	return (newfile);
}