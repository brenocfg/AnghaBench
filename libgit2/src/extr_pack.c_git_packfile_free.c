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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct git_pack_file {TYPE_1__ bases; int /*<<< orphan*/  lock; struct git_pack_file* bad_object_sha1; } ;

/* Variables and functions */
 int /*<<< orphan*/  cache_free (TYPE_1__*) ; 
 int /*<<< orphan*/  git__free (struct git_pack_file*) ; 
 int /*<<< orphan*/  git_mutex_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_packfile_close (struct git_pack_file*,int) ; 
 int /*<<< orphan*/  pack_index_free (struct git_pack_file*) ; 

void git_packfile_free(struct git_pack_file *p)
{
	if (!p)
		return;

	cache_free(&p->bases);

	git_packfile_close(p, false);

	pack_index_free(p);

	git__free(p->bad_object_sha1);

	git_mutex_free(&p->lock);
	git_mutex_free(&p->bases.lock);
	git__free(p);
}