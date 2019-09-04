#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {char* buf; } ;
struct sliding_view {TYPE_1__ buf; scalar_t__ max_off; } ;
struct line_buffer {int dummy; } ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 struct sliding_view SLIDING_VIEW_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ S_IFLNK ; 
 int /*<<< orphan*/  assert (int) ; 
 long buffer_tmpfile_prepare_to_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * buffer_tmpfile_rewind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_preimage_overflow (scalar_t__,int) ; 
 int /*<<< orphan*/  die (char*,...) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 char* get_response_line () ; 
 scalar_t__ init_postimage () ; 
 scalar_t__ move_window (struct sliding_view*,scalar_t__,int) ; 
 scalar_t__ parse_cat_response_line (char const*,scalar_t__*) ; 
 int /*<<< orphan*/  postimage ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  report_buffer ; 
 int /*<<< orphan*/  signed_add_overflows (scalar_t__,int) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strbuf_addstr (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  strbuf_release (TYPE_1__*) ; 
 int strlen (char*) ; 
 scalar_t__ svndiff0_apply (struct line_buffer*,int /*<<< orphan*/ ,struct sliding_view*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static long apply_delta(off_t len, struct line_buffer *input,
			const char *old_data, uint32_t old_mode)
{
	long ret;
	struct sliding_view preimage = SLIDING_VIEW_INIT(&report_buffer, 0);
	FILE *out;

	if (init_postimage() || !(out = buffer_tmpfile_rewind(&postimage)))
		die("cannot open temporary file for blob retrieval");
	if (old_data) {
		const char *response;
		printf("cat-blob %s\n", old_data);
		fflush(stdout);
		response = get_response_line();
		if (parse_cat_response_line(response, &preimage.max_off))
			die("invalid cat-blob response: %s", response);
		check_preimage_overflow(preimage.max_off, 1);
	}
	if (old_mode == S_IFLNK) {
		strbuf_addstr(&preimage.buf, "link ");
		check_preimage_overflow(preimage.max_off, strlen("link "));
		preimage.max_off += strlen("link ");
		check_preimage_overflow(preimage.max_off, 1);
	}
	if (svndiff0_apply(input, len, &preimage, out))
		die("cannot apply delta");
	if (old_data) {
		/* Read the remainder of preimage and trailing newline. */
		assert(!signed_add_overflows(preimage.max_off, 1));
		preimage.max_off++;	/* room for newline */
		if (move_window(&preimage, preimage.max_off - 1, 1))
			die("cannot seek to end of input");
		if (preimage.buf.buf[0] != '\n')
			die("missing newline after cat-blob response");
	}
	ret = buffer_tmpfile_prepare_to_read(&postimage);
	if (ret < 0)
		die("cannot read temporary file for blob retrieval");
	strbuf_release(&preimage.buf);
	return ret;
}