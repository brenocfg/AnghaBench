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
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct packed_git {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 struct packed_git* add_packed_git (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chmod (char const*,int) ; 
 int close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ) ; 
 scalar_t__ do_fsck_object ; 
 scalar_t__ finalize_object_file (char const*,char const*) ; 
 scalar_t__ from_stdin ; 
 int /*<<< orphan*/  fsync_or_die (int /*<<< orphan*/ ,char const*) ; 
 char* hash_to_hex (unsigned char*) ; 
 scalar_t__ input_buffer ; 
 int /*<<< orphan*/  input_fd ; 
 scalar_t__ input_len ; 
 scalar_t__ input_offset ; 
 int /*<<< orphan*/  install_packed_git (int /*<<< orphan*/ ,struct packed_git*) ; 
 char* odb_pack_name (struct strbuf*,unsigned char*,char*) ; 
 int /*<<< orphan*/  output_fd ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*,char*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  write_or_die (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_special_file (char*,char const*,char const*,unsigned char*,char const**) ; 
 int xwrite (int,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void final(const char *final_pack_name, const char *curr_pack_name,
		  const char *final_index_name, const char *curr_index_name,
		  const char *keep_msg, const char *promisor_msg,
		  unsigned char *hash)
{
	const char *report = "pack";
	struct strbuf pack_name = STRBUF_INIT;
	struct strbuf index_name = STRBUF_INIT;
	int err;

	if (!from_stdin) {
		close(input_fd);
	} else {
		fsync_or_die(output_fd, curr_pack_name);
		err = close(output_fd);
		if (err)
			die_errno(_("error while closing pack file"));
	}

	if (keep_msg)
		write_special_file("keep", keep_msg, final_pack_name, hash,
				   &report);
	if (promisor_msg)
		write_special_file("promisor", promisor_msg, final_pack_name,
				   hash, NULL);

	if (final_pack_name != curr_pack_name) {
		if (!final_pack_name)
			final_pack_name = odb_pack_name(&pack_name, hash, "pack");
		if (finalize_object_file(curr_pack_name, final_pack_name))
			die(_("cannot store pack file"));
	} else if (from_stdin)
		chmod(final_pack_name, 0444);

	if (final_index_name != curr_index_name) {
		if (!final_index_name)
			final_index_name = odb_pack_name(&index_name, hash, "idx");
		if (finalize_object_file(curr_index_name, final_index_name))
			die(_("cannot store index file"));
	} else
		chmod(final_index_name, 0444);

	if (do_fsck_object) {
		struct packed_git *p;
		p = add_packed_git(final_index_name, strlen(final_index_name), 0);
		if (p)
			install_packed_git(the_repository, p);
	}

	if (!from_stdin) {
		printf("%s\n", hash_to_hex(hash));
	} else {
		struct strbuf buf = STRBUF_INIT;

		strbuf_addf(&buf, "%s\t%s\n", report, hash_to_hex(hash));
		write_or_die(1, buf.buf, buf.len);
		strbuf_release(&buf);

		/*
		 * Let's just mimic git-unpack-objects here and write
		 * the last part of the input buffer to stdout.
		 */
		while (input_len) {
			err = xwrite(1, input_buffer + input_offset, input_len);
			if (err <= 0)
				break;
			input_len -= err;
			input_offset += err;
		}
	}

	strbuf_release(&index_name);
	strbuf_release(&pack_name);
}