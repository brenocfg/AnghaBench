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
typedef  scalar_t__ uint32_t ;
struct strbuf {char* buf; } ;
struct repository {int dummy; } ;
struct object_id {int dummy; } ;
struct multi_pack_index {scalar_t__ num_objects; int /*<<< orphan*/  num_packs; } ;
struct child_process {int git_cmd; int in; int out; int /*<<< orphan*/  args; } ;
struct TYPE_2__ {int hexsz; } ;

/* Variables and functions */
 struct child_process CHILD_PROCESS_INIT ; 
 unsigned int MIDX_PROGRESS ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  argv_array_push (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  close_midx (struct multi_pack_index*) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ) ; 
 scalar_t__ fill_included_packs_all (struct multi_pack_index*,unsigned char*) ; 
 scalar_t__ fill_included_packs_batch (struct repository*,struct multi_pack_index*,unsigned char*,size_t) ; 
 scalar_t__ finish_command (struct child_process*) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 struct multi_pack_index* load_multi_pack_index (char const*,int) ; 
 int /*<<< orphan*/  nth_midxed_object_oid (struct object_id*,struct multi_pack_index*,scalar_t__) ; 
 scalar_t__ nth_midxed_pack_int_id (struct multi_pack_index*,scalar_t__) ; 
 char* oid_to_hex (struct object_id*) ; 
 scalar_t__ start_command (struct child_process*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 TYPE_1__* the_hash_algo ; 
 int write_midx_internal (char const*,struct multi_pack_index*,int /*<<< orphan*/ *,unsigned int) ; 
 unsigned char* xcalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xwrite (int,char*,int) ; 

int midx_repack(struct repository *r, const char *object_dir, size_t batch_size, unsigned flags)
{
	int result = 0;
	uint32_t i;
	unsigned char *include_pack;
	struct child_process cmd = CHILD_PROCESS_INIT;
	struct strbuf base_name = STRBUF_INIT;
	struct multi_pack_index *m = load_multi_pack_index(object_dir, 1);

	if (!m)
		return 0;

	include_pack = xcalloc(m->num_packs, sizeof(unsigned char));

	if (batch_size) {
		if (fill_included_packs_batch(r, m, include_pack, batch_size))
			goto cleanup;
	} else if (fill_included_packs_all(m, include_pack))
		goto cleanup;

	argv_array_push(&cmd.args, "pack-objects");

	strbuf_addstr(&base_name, object_dir);
	strbuf_addstr(&base_name, "/pack/pack");
	argv_array_push(&cmd.args, base_name.buf);

	if (flags & MIDX_PROGRESS)
		argv_array_push(&cmd.args, "--progress");
	else
		argv_array_push(&cmd.args, "-q");

	strbuf_release(&base_name);

	cmd.git_cmd = 1;
	cmd.in = cmd.out = -1;

	if (start_command(&cmd)) {
		error(_("could not start pack-objects"));
		result = 1;
		goto cleanup;
	}

	for (i = 0; i < m->num_objects; i++) {
		struct object_id oid;
		uint32_t pack_int_id = nth_midxed_pack_int_id(m, i);

		if (!include_pack[pack_int_id])
			continue;

		nth_midxed_object_oid(&oid, m, i);
		xwrite(cmd.in, oid_to_hex(&oid), the_hash_algo->hexsz);
		xwrite(cmd.in, "\n", 1);
	}
	close(cmd.in);

	if (finish_command(&cmd)) {
		error(_("could not finish pack-objects"));
		result = 1;
		goto cleanup;
	}

	result = write_midx_internal(object_dir, m, NULL, flags);
	m = NULL;

cleanup:
	if (m)
		close_midx(m);
	free(include_pack);
	return result;
}