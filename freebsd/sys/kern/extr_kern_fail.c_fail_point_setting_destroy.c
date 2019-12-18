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
struct fail_point_setting {int /*<<< orphan*/  fp_entry_queue; } ;
struct fail_point_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct fail_point_entry* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct fail_point_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fail_point_entry_destroy (struct fail_point_entry*) ; 
 int /*<<< orphan*/  fe_entries ; 
 int /*<<< orphan*/  fs_free (struct fail_point_setting*) ; 

__attribute__((used)) static void
fail_point_setting_destroy(struct fail_point_setting *fp_setting)
{
	struct fail_point_entry *ent;

	while (!TAILQ_EMPTY(&fp_setting->fp_entry_queue)) {
		ent = TAILQ_FIRST(&fp_setting->fp_entry_queue);
		TAILQ_REMOVE(&fp_setting->fp_entry_queue, ent, fe_entries);
		fail_point_entry_destroy(ent);
	}

	fs_free(fp_setting);
}