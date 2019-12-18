#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct progress_info {int /*<<< orphan*/  blamed_lines; int /*<<< orphan*/  progress; } ;
struct blame_origin {TYPE_2__* commit; } ;
struct blame_entry {int s_lno; int lno; int num_lines; struct blame_origin* suspect; } ;
struct TYPE_3__ {int /*<<< orphan*/  oid; } ;
struct TYPE_4__ {TYPE_1__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  display_progress (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_one_suspect_detail (struct blame_origin*,int /*<<< orphan*/ ) ; 
 scalar_t__ incremental ; 
 int /*<<< orphan*/  maybe_flush_or_die (int /*<<< orphan*/ ,char*) ; 
 char* oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*,int,int,int) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  write_filename_info (struct blame_origin*) ; 

__attribute__((used)) static void found_guilty_entry(struct blame_entry *ent, void *data)
{
	struct progress_info *pi = (struct progress_info *)data;

	if (incremental) {
		struct blame_origin *suspect = ent->suspect;

		printf("%s %d %d %d\n",
		       oid_to_hex(&suspect->commit->object.oid),
		       ent->s_lno + 1, ent->lno + 1, ent->num_lines);
		emit_one_suspect_detail(suspect, 0);
		write_filename_info(suspect);
		maybe_flush_or_die(stdout, "stdout");
	}
	pi->blamed_lines += ent->num_lines;
	display_progress(pi->progress, pi->blamed_lines);
}