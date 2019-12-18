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
struct strbuf {int /*<<< orphan*/  buf; } ;
struct stat {int dummy; } ;
struct object_id {int dummy; } ;
struct child_process {char const** argv; int git_cmd; int in; int out; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;
struct TYPE_4__ {scalar_t__ hexsz; } ;
struct TYPE_3__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 struct child_process CHILD_PROCESS_INIT ; 
 int HASH_FORMAT_CHECK ; 
 int HASH_WRITE_OBJECT ; 
 int OBJ_TREE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int error (int /*<<< orphan*/ ) ; 
 int error_errno (int /*<<< orphan*/ ,...) ; 
 scalar_t__ finish_command (struct child_process*) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 scalar_t__ get_oid_hex (int /*<<< orphan*/ ,struct object_id*) ; 
 scalar_t__ index_fd (int /*<<< orphan*/ ,struct object_id*,int,struct stat*,int,int /*<<< orphan*/ *,int) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ start_command (struct child_process*) ; 
 scalar_t__ strbuf_read (struct strbuf*,int,scalar_t__) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 TYPE_2__* the_hash_algo ; 
 TYPE_1__* the_repository ; 

__attribute__((used)) static int import_object(struct object_id *oid, enum object_type type,
			  int raw, const char *filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return error_errno(_("unable to open %s for reading"), filename);

	if (!raw && type == OBJ_TREE) {
		const char *argv[] = { "mktree", NULL };
		struct child_process cmd = CHILD_PROCESS_INIT;
		struct strbuf result = STRBUF_INIT;

		cmd.argv = argv;
		cmd.git_cmd = 1;
		cmd.in = fd;
		cmd.out = -1;

		if (start_command(&cmd)) {
			close(fd);
			return error(_("unable to spawn mktree"));
		}

		if (strbuf_read(&result, cmd.out, the_hash_algo->hexsz + 1) < 0) {
			error_errno(_("unable to read from mktree"));
			close(fd);
			close(cmd.out);
			return -1;
		}
		close(cmd.out);

		if (finish_command(&cmd)) {
			strbuf_release(&result);
			return error(_("mktree reported failure"));
		}
		if (get_oid_hex(result.buf, oid) < 0) {
			strbuf_release(&result);
			return error(_("mktree did not return an object name"));
		}

		strbuf_release(&result);
	} else {
		struct stat st;
		int flags = HASH_FORMAT_CHECK | HASH_WRITE_OBJECT;

		if (fstat(fd, &st) < 0) {
			error_errno(_("unable to fstat %s"), filename);
			close(fd);
			return -1;
		}
		if (index_fd(the_repository->index, oid, fd, &st, type, NULL, flags) < 0)
			return error(_("unable to write object to database"));
		/* index_fd close()s fd for us */
	}

	/*
	 * No need to close(fd) here; both run-command and index-fd
	 * will have done it for us.
	 */
	return 0;
}