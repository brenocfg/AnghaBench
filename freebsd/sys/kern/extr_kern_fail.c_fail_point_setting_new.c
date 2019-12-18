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
struct fail_point_setting {int /*<<< orphan*/  feq_mtx; int /*<<< orphan*/  fp_entry_queue; struct fail_point* fs_parent; } ;
struct fail_point {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_SPIN ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fail_point_setting_garbage_append (struct fail_point_setting*) ; 
 struct fail_point_setting* fs_malloc () ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct fail_point_setting *
fail_point_setting_new(struct fail_point *fp)
{
	struct fail_point_setting *fs_new;

	fs_new = fs_malloc();
	fs_new->fs_parent = fp;
	TAILQ_INIT(&fs_new->fp_entry_queue);
	mtx_init(&fs_new->feq_mtx, "fail point entries", NULL, MTX_SPIN);

	fail_point_setting_garbage_append(fs_new);

	return (fs_new);
}