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
struct line_buffer {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  buffer_copy_bytes (struct line_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer_read_binary (struct line_buffer*,struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer_skip_bytes (struct line_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (char*,char const*) ; 
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ starts_with (char const*,char*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strtouint32 (char const*) ; 

__attribute__((used)) static void handle_command(const char *command, const char *arg, struct line_buffer *buf)
{
	if (starts_with(command, "binary ")) {
		struct strbuf sb = STRBUF_INIT;
		strbuf_addch(&sb, '>');
		buffer_read_binary(buf, &sb, strtouint32(arg));
		fwrite(sb.buf, 1, sb.len, stdout);
		strbuf_release(&sb);
	} else if (starts_with(command, "copy ")) {
		buffer_copy_bytes(buf, strtouint32(arg));
	} else if (starts_with(command, "skip ")) {
		buffer_skip_bytes(buf, strtouint32(arg));
	} else {
		die("unrecognized command: %s", command);
	}
}