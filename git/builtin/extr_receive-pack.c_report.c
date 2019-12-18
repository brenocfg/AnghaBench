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
struct command {int /*<<< orphan*/  error_string; int /*<<< orphan*/  ref_name; struct command* next; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  packet_buf_flush (struct strbuf*) ; 
 int /*<<< orphan*/  packet_buf_write (struct strbuf*,char*,char const*,...) ; 
 int /*<<< orphan*/  send_sideband (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 scalar_t__ use_sideband ; 
 int /*<<< orphan*/  write_or_die (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void report(struct command *commands, const char *unpack_status)
{
	struct command *cmd;
	struct strbuf buf = STRBUF_INIT;

	packet_buf_write(&buf, "unpack %s\n",
			 unpack_status ? unpack_status : "ok");
	for (cmd = commands; cmd; cmd = cmd->next) {
		if (!cmd->error_string)
			packet_buf_write(&buf, "ok %s\n",
					 cmd->ref_name);
		else
			packet_buf_write(&buf, "ng %s %s\n",
					 cmd->ref_name, cmd->error_string);
	}
	packet_buf_flush(&buf);

	if (use_sideband)
		send_sideband(1, 1, buf.buf, buf.len, use_sideband);
	else
		write_or_die(1, buf.buf, buf.len);
	strbuf_release(&buf);
}