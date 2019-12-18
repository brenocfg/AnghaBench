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
typedef  int /*<<< orphan*/  uint32_t ;
struct packed_git {int dummy; } ;
struct object_id {int dummy; } ;
struct child_process {int in; } ;
struct TYPE_2__ {int hexsz; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 char* oid_to_hex (struct object_id const*) ; 
 scalar_t__ start_command (struct child_process*) ; 
 TYPE_1__* the_hash_algo ; 
 int /*<<< orphan*/  xwrite (int,char*,int) ; 

__attribute__((used)) static int write_oid(const struct object_id *oid, struct packed_git *pack,
		     uint32_t pos, void *data)
{
	struct child_process *cmd = data;

	if (cmd->in == -1) {
		if (start_command(cmd))
			die(_("could not start pack-objects to repack promisor objects"));
	}

	xwrite(cmd->in, oid_to_hex(oid), the_hash_algo->hexsz);
	xwrite(cmd->in, "\n", 1);
	return 0;
}