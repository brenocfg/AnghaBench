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
struct string_list {int dummy; } ;
struct receive_hook_feed_state {int skip_broken; int /*<<< orphan*/  buf; struct string_list const* push_options; struct command* cmd; } ;
struct command {int dummy; } ;

/* Variables and functions */
 scalar_t__ feed_receive_hook (struct receive_hook_feed_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int run_and_feed_hook (char const*,scalar_t__ (*) (struct receive_hook_feed_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ *),struct receive_hook_feed_state*) ; 
 int /*<<< orphan*/  strbuf_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int run_receive_hook(struct command *commands,
			    const char *hook_name,
			    int skip_broken,
			    const struct string_list *push_options)
{
	struct receive_hook_feed_state state;
	int status;

	strbuf_init(&state.buf, 0);
	state.cmd = commands;
	state.skip_broken = skip_broken;
	if (feed_receive_hook(&state, NULL, NULL))
		return 0;
	state.cmd = commands;
	state.push_options = push_options;
	status = run_and_feed_hook(hook_name, feed_receive_hook, &state);
	strbuf_release(&state.buf);
	return status;
}