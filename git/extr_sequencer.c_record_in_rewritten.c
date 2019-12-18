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
struct object_id {int dummy; } ;
typedef  enum todo_command { ____Placeholder_todo_command } todo_command ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_rewritten_pending () ; 
 int /*<<< orphan*/ * fopen_or_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  is_fixup (int) ; 
 char* oid_to_hex (struct object_id*) ; 
 int /*<<< orphan*/  rebase_path_rewritten_pending () ; 

__attribute__((used)) static void record_in_rewritten(struct object_id *oid,
		enum todo_command next_command)
{
	FILE *out = fopen_or_warn(rebase_path_rewritten_pending(), "a");

	if (!out)
		return;

	fprintf(out, "%s\n", oid_to_hex(oid));
	fclose(out);

	if (!is_fixup(next_command))
		flush_rewritten_pending();
}