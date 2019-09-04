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
struct strbuf {int /*<<< orphan*/  buf; } ;
struct replay_opts {int xopts_nr; int /*<<< orphan*/ * xopts; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  rebase_path_strategy_opts () ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  write_file (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_strategy_opts(struct replay_opts *opts)
{
	int i;
	struct strbuf buf = STRBUF_INIT;

	for (i = 0; i < opts->xopts_nr; ++i)
		strbuf_addf(&buf, " --%s", opts->xopts[i]);

	write_file(rebase_path_strategy_opts(), "%s\n", buf.buf);
	strbuf_release(&buf);
}