#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  ptr; scalar_t__ size; } ;
struct TYPE_5__ {TYPE_2__ line; int /*<<< orphan*/  driver; int /*<<< orphan*/  (* match_line ) (int /*<<< orphan*/ ,TYPE_2__*) ;} ;
typedef  TYPE_1__ git_diff_find_context_payload ;

/* Variables and functions */
 int /*<<< orphan*/  git_buf_rtrim (TYPE_2__*) ; 
 scalar_t__ git_buf_set (TYPE_2__*,char const*,size_t) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static long diff_context_find(
	const char *line,
	long line_len,
	char *out,
	long out_size,
	void *payload)
{
	git_diff_find_context_payload *ctxt = payload;

	if (git_buf_set(&ctxt->line, line, (size_t)line_len) < 0)
		return -1;
	git_buf_rtrim(&ctxt->line);

	if (!ctxt->line.size)
		return -1;

	if (!ctxt->match_line || !ctxt->match_line(ctxt->driver, &ctxt->line))
		return -1;

	if (out_size > (long)ctxt->line.size)
		out_size = (long)ctxt->line.size;
	memcpy(out, ctxt->line.ptr, (size_t)out_size);

	return out_size;
}