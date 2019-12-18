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
struct strbuf {int dummy; } ;
struct filter_params {char const* src; size_t size; int fd; char const* cmd; char const* path; } ;
struct async {int out; struct filter_params* data; int /*<<< orphan*/  proc; } ;
typedef  int /*<<< orphan*/  async ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ close (int) ; 
 int error (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  filter_buffer_or_fd ; 
 scalar_t__ finish_async (struct async*) ; 
 int /*<<< orphan*/  memset (struct async*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ start_async (struct async*) ; 
 scalar_t__ strbuf_read (struct strbuf*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_swap (struct strbuf*,struct strbuf*) ; 

__attribute__((used)) static int apply_single_file_filter(const char *path, const char *src, size_t len, int fd,
				    struct strbuf *dst, const char *cmd)
{
	/*
	 * Create a pipeline to have the command filter the buffer's
	 * contents.
	 *
	 * (child --> cmd) --> us
	 */
	int err = 0;
	struct strbuf nbuf = STRBUF_INIT;
	struct async async;
	struct filter_params params;

	memset(&async, 0, sizeof(async));
	async.proc = filter_buffer_or_fd;
	async.data = &params;
	async.out = -1;
	params.src = src;
	params.size = len;
	params.fd = fd;
	params.cmd = cmd;
	params.path = path;

	fflush(NULL);
	if (start_async(&async))
		return 0;	/* error was already reported */

	if (strbuf_read(&nbuf, async.out, 0) < 0) {
		err = error(_("read from external filter '%s' failed"), cmd);
	}
	if (close(async.out)) {
		err = error(_("read from external filter '%s' failed"), cmd);
	}
	if (finish_async(&async)) {
		err = error(_("external filter '%s' failed"), cmd);
	}

	if (!err) {
		strbuf_swap(dst, &nbuf);
	}
	strbuf_release(&nbuf);
	return !err;
}