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
struct replay_opts {int /*<<< orphan*/  strategy; } ;

/* Variables and functions */
 int /*<<< orphan*/  parse_strategy_opts (struct replay_opts*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_oneliner (struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rebase_path_strategy () ; 
 int /*<<< orphan*/  rebase_path_strategy_opts () ; 
 int /*<<< orphan*/  strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 

__attribute__((used)) static void read_strategy_opts(struct replay_opts *opts, struct strbuf *buf)
{
	strbuf_reset(buf);
	if (!read_oneliner(buf, rebase_path_strategy(), 0))
		return;
	opts->strategy = strbuf_detach(buf, NULL);
	if (!read_oneliner(buf, rebase_path_strategy_opts(), 0))
		return;

	parse_strategy_opts(opts, buf->buf);
}