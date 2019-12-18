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
struct TYPE_2__ {int fd; } ;
struct git_pack_file {int /*<<< orphan*/  pack_name; TYPE_1__ mwf; } ;

/* Variables and functions */
 int /*<<< orphan*/  git_mwindow_free_all_locked (TYPE_1__*) ; 
 int /*<<< orphan*/  p_close (int) ; 
 int /*<<< orphan*/  p_unlink (int /*<<< orphan*/ ) ; 

void git_packfile_close(struct git_pack_file *p, bool unlink_packfile)
{
	if (p->mwf.fd >= 0) {
		git_mwindow_free_all_locked(&p->mwf);
		p_close(p->mwf.fd);
		p->mwf.fd = -1;
	}

	if (unlink_packfile)
		p_unlink(p->pack_name);
}