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
struct group {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  etcpath; } ;

/* Variables and functions */
 struct group* GETGRNAM (char const*) ; 
 int /*<<< orphan*/  close (int) ; 
 TYPE_1__ conf ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  free (struct group*) ; 
 int /*<<< orphan*/  fsync (int) ; 
 int gr_copy (int,int,struct group*,struct group*) ; 
 struct group* gr_dup (struct group*) ; 
 int /*<<< orphan*/  gr_fini () ; 
 scalar_t__ gr_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int gr_lock () ; 
 int gr_mkdb () ; 
 int gr_tmp (int) ; 

__attribute__((used)) static int
gr_update(struct group * grp, char const * group)
{
	int pfd, tfd;
	struct group *gr = NULL;
	struct group *old_gr = NULL;

	if (grp != NULL)
		gr = gr_dup(grp);

	if (group != NULL)
		old_gr = GETGRNAM(group);

	if (gr_init(conf.etcpath, NULL))
		err(1, "gr_init()");

	if ((pfd = gr_lock()) == -1) {
		gr_fini();
		err(1, "gr_lock()");
	}
	if ((tfd = gr_tmp(-1)) == -1) {
		gr_fini();
		err(1, "gr_tmp()");
	}
	if (gr_copy(pfd, tfd, gr, old_gr) == -1) {
		gr_fini();
		close(tfd);
		err(1, "gr_copy()");
	}
	fsync(tfd);
	close(tfd);
	if (gr_mkdb() == -1) {
		gr_fini();
		err(1, "gr_mkdb()");
	}
	free(gr);
	gr_fini();
	return 0;
}