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
struct fail_point_setting {int /*<<< orphan*/  fp_entry_queue; int /*<<< orphan*/  fs_parent; } ;
struct fail_point_entry {int /*<<< orphan*/  fe_count; int /*<<< orphan*/  fe_pid; int /*<<< orphan*/  fe_prob; int /*<<< orphan*/  fe_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  FE_COUNT_UNTRACKED ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NO_PID ; 
 int /*<<< orphan*/  PROB_MAX ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct fail_point_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fe_entries ; 
 struct fail_point_entry* fp_malloc (int,int) ; 

__attribute__((used)) static struct fail_point_entry *
fail_point_entry_new(struct fail_point_setting *fp_setting)
{
	struct fail_point_entry *fp_entry;

	fp_entry = fp_malloc(sizeof(struct fail_point_entry),
	        M_WAITOK | M_ZERO);
	fp_entry->fe_parent = fp_setting->fs_parent;
	fp_entry->fe_prob = PROB_MAX;
	fp_entry->fe_pid = NO_PID;
	fp_entry->fe_count = FE_COUNT_UNTRACKED;
	TAILQ_INSERT_TAIL(&fp_setting->fp_entry_queue, fp_entry,
	        fe_entries);

	return (fp_entry);
}