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
struct config_source {int linenr; struct config_source* prev; int /*<<< orphan*/  var; int /*<<< orphan*/  value; scalar_t__ eof; } ;
struct config_options {int dummy; } ;
typedef  int /*<<< orphan*/  config_fn_t ;

/* Variables and functions */
 struct config_source* cf ; 
 int git_parse_source (int /*<<< orphan*/ ,void*,struct config_options const*) ; 
 int /*<<< orphan*/  strbuf_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strbuf_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int do_config_from(struct config_source *top, config_fn_t fn, void *data,
			  const struct config_options *opts)
{
	int ret;

	/* push config-file parsing state stack */
	top->prev = cf;
	top->linenr = 1;
	top->eof = 0;
	strbuf_init(&top->value, 1024);
	strbuf_init(&top->var, 1024);
	cf = top;

	ret = git_parse_source(fn, data, opts);

	/* pop config-file parsing state stack */
	strbuf_release(&top->value);
	strbuf_release(&top->var);
	cf = top->prev;

	return ret;
}