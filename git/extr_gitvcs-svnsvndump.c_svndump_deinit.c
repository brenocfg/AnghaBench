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
struct TYPE_4__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct TYPE_3__ {int /*<<< orphan*/  note; int /*<<< orphan*/  author; int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ buffer_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fast_export_deinit () ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  input ; 
 TYPE_2__ node_ctx ; 
 int /*<<< orphan*/  reset_dump_ctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_node_ctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_rev_ctx (int /*<<< orphan*/ ) ; 
 TYPE_1__ rev_ctx ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strbuf_release (int /*<<< orphan*/ *) ; 

void svndump_deinit(void)
{
	fast_export_deinit();
	reset_dump_ctx(NULL);
	reset_rev_ctx(0);
	reset_node_ctx(NULL);
	strbuf_release(&rev_ctx.log);
	strbuf_release(&rev_ctx.author);
	strbuf_release(&rev_ctx.note);
	strbuf_release(&node_ctx.src);
	strbuf_release(&node_ctx.dst);
	if (buffer_deinit(&input))
		fprintf(stderr, "Input error\n");
	if (ferror(stdout))
		fprintf(stderr, "Output error\n");
}