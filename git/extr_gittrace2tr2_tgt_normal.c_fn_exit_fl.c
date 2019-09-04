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
typedef  scalar_t__ uint64_t ;
struct strbuf {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  normal_io_write_fl (char const*,int,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,double,int) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void fn_exit_fl(const char *file, int line, uint64_t us_elapsed_absolute,
		       int code)
{
	struct strbuf buf_payload = STRBUF_INIT;
	double elapsed = (double)us_elapsed_absolute / 1000000.0;

	strbuf_addf(&buf_payload, "exit elapsed:%.6f code:%d", elapsed, code);
	normal_io_write_fl(file, line, &buf_payload);
	strbuf_release(&buf_payload);
}