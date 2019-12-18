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
typedef  int /*<<< orphan*/  uint64_t ;
struct strbuf {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  normal_io_write_fl (char const*,int,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int,...) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strerror (int) ; 

__attribute__((used)) static void fn_exec_result_fl(const char *file, int line,
			      uint64_t us_elapsed_absolute, int exec_id,
			      int code)
{
	struct strbuf buf_payload = STRBUF_INIT;

	strbuf_addf(&buf_payload, "exec_result[%d] code:%d", exec_id, code);
	if (code > 0)
		strbuf_addf(&buf_payload, " err:%s", strerror(code));
	normal_io_write_fl(file, line, &buf_payload);
	strbuf_release(&buf_payload);
}