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
struct grep_source {int dummy; } ;
struct grep_opt {int /*<<< orphan*/  prefix; scalar_t__ prefix_length; scalar_t__ relative; } ;

/* Variables and functions */
 int /*<<< orphan*/  GREP_SOURCE_FILE ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  add_work (struct grep_opt*,struct grep_source*) ; 
 int grep_source (struct grep_opt*,struct grep_source*) ; 
 int /*<<< orphan*/  grep_source_clear (struct grep_source*) ; 
 int /*<<< orphan*/  grep_source_init (struct grep_source*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const*) ; 
 int num_threads ; 
 int /*<<< orphan*/  quote_path_relative (char const*,int /*<<< orphan*/ ,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static int grep_file(struct grep_opt *opt, const char *filename)
{
	struct strbuf buf = STRBUF_INIT;
	struct grep_source gs;

	if (opt->relative && opt->prefix_length)
		quote_path_relative(filename, opt->prefix, &buf);
	else
		strbuf_addstr(&buf, filename);

	grep_source_init(&gs, GREP_SOURCE_FILE, buf.buf, filename, filename);
	strbuf_release(&buf);

	if (num_threads > 1) {
		/*
		 * add_work() copies gs and thus assumes ownership of
		 * its fields, so do not call grep_source_clear()
		 */
		add_work(opt, &gs);
		return 0;
	} else {
		int hit;

		hit = grep_source(opt, &gs);

		grep_source_clear(&gs);
		return hit;
	}
}