#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int nr; TYPE_1__* objects; } ;
struct rev_info {TYPE_2__ pending; } ;
struct object {int flags; int /*<<< orphan*/  oid; } ;
struct child_process {int in; int out; int git_cmd; int /*<<< orphan*/  args; } ;
struct TYPE_6__ {int hexsz; } ;
struct TYPE_4__ {struct object* item; } ;

/* Variables and functions */
 struct child_process CHILD_PROCESS_INIT ; 
 int UNINTERESTING ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  argv_array_pushl (int /*<<< orphan*/ *,char*,char*,char*,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  child_process_clear (struct child_process*) ; 
 int /*<<< orphan*/  close (int) ; 
 int dup (int) ; 
 int error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error_errno (int /*<<< orphan*/ ) ; 
 scalar_t__ finish_command (struct child_process*) ; 
 char* oid_to_hex (int /*<<< orphan*/ *) ; 
 scalar_t__ start_command (struct child_process*) ; 
 TYPE_3__* the_hash_algo ; 
 int /*<<< orphan*/  write_or_die (int,char*,int) ; 

__attribute__((used)) static int write_pack_data(int bundle_fd, struct rev_info *revs)
{
	struct child_process pack_objects = CHILD_PROCESS_INIT;
	int i;

	argv_array_pushl(&pack_objects.args,
			 "pack-objects", "--all-progress-implied",
			 "--stdout", "--thin", "--delta-base-offset",
			 NULL);
	pack_objects.in = -1;
	pack_objects.out = bundle_fd;
	pack_objects.git_cmd = 1;

	/*
	 * start_command() will close our descriptor if it's >1. Duplicate it
	 * to avoid surprising the caller.
	 */
	if (pack_objects.out > 1) {
		pack_objects.out = dup(pack_objects.out);
		if (pack_objects.out < 0) {
			error_errno(_("unable to dup bundle descriptor"));
			child_process_clear(&pack_objects);
			return -1;
		}
	}

	if (start_command(&pack_objects))
		return error(_("Could not spawn pack-objects"));

	for (i = 0; i < revs->pending.nr; i++) {
		struct object *object = revs->pending.objects[i].item;
		if (object->flags & UNINTERESTING)
			write_or_die(pack_objects.in, "^", 1);
		write_or_die(pack_objects.in, oid_to_hex(&object->oid), the_hash_algo->hexsz);
		write_or_die(pack_objects.in, "\n", 1);
	}
	close(pack_objects.in);
	if (finish_command(&pack_objects))
		return error(_("pack-objects died"));
	return 0;
}