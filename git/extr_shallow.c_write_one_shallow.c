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
struct write_shallow_data {int flags; int /*<<< orphan*/  out; scalar_t__ use_pack_protocol; int /*<<< orphan*/  count; } ;
struct commit_graft {int nr_parent; int /*<<< orphan*/  oid; } ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  oid; } ;
struct commit {TYPE_1__ object; } ;

/* Variables and functions */
 int QUICK ; 
 int SEEN ; 
 int SEEN_ONLY ; 
 int VERBOSE ; 
 int /*<<< orphan*/  has_object_file (int /*<<< orphan*/ *) ; 
 struct commit* lookup_commit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  packet_buf_write (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  strbuf_addch (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  strbuf_addstr (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static int write_one_shallow(const struct commit_graft *graft, void *cb_data)
{
	struct write_shallow_data *data = cb_data;
	const char *hex = oid_to_hex(&graft->oid);
	if (graft->nr_parent != -1)
		return 0;
	if (data->flags & QUICK) {
		if (!has_object_file(&graft->oid))
			return 0;
	} else if (data->flags & SEEN_ONLY) {
		struct commit *c = lookup_commit(the_repository, &graft->oid);
		if (!c || !(c->object.flags & SEEN)) {
			if (data->flags & VERBOSE)
				printf("Removing %s from .git/shallow\n",
				       oid_to_hex(&c->object.oid));
			return 0;
		}
	}
	data->count++;
	if (data->use_pack_protocol)
		packet_buf_write(data->out, "shallow %s", hex);
	else {
		strbuf_addstr(data->out, hex);
		strbuf_addch(data->out, '\n');
	}
	return 0;
}