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
struct line_buffer {int dummy; } ;

/* Variables and functions */
 struct line_buffer LINE_BUFFER_INIT ; 
 scalar_t__ buffer_deinit (struct line_buffer*) ; 
 scalar_t__ buffer_fdinit (struct line_buffer*,int /*<<< orphan*/ ) ; 
 scalar_t__ buffer_init (struct line_buffer*,char const*) ; 
 char* buffer_read_line (struct line_buffer*) ; 
 int /*<<< orphan*/  die (char*,...) ; 
 int /*<<< orphan*/  die_errno (char*,...) ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_line (char*,struct line_buffer*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strtouint32 (char const*) ; 
 int /*<<< orphan*/  usage (char*) ; 

int cmd_main(int argc, const char **argv)
{
	struct line_buffer stdin_buf = LINE_BUFFER_INIT;
	struct line_buffer file_buf = LINE_BUFFER_INIT;
	struct line_buffer *input = &stdin_buf;
	const char *filename;
	char *s;

	if (argc == 1)
		filename = NULL;
	else if (argc == 2)
		filename = argv[1];
	else
		usage("test-line-buffer [file | &fd] < script");

	if (buffer_init(&stdin_buf, NULL))
		die_errno("open error");
	if (filename) {
		if (*filename == '&') {
			if (buffer_fdinit(&file_buf, strtouint32(filename + 1)))
				die_errno("error opening fd %s", filename + 1);
		} else {
			if (buffer_init(&file_buf, filename))
				die_errno("error opening %s", filename);
		}
		input = &file_buf;
	}

	while ((s = buffer_read_line(&stdin_buf)))
		handle_line(s, input);

	if (filename && buffer_deinit(&file_buf))
		die("error reading from %s", filename);
	if (buffer_deinit(&stdin_buf))
		die("input error");
	if (ferror(stdout))
		die("output error");
	return 0;
}