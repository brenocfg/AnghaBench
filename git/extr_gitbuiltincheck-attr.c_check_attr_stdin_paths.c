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
struct strbuf {char* buf; } ;
struct attr_check {int dummy; } ;
typedef  scalar_t__ (* strbuf_getline_fn ) (struct strbuf*,int /*<<< orphan*/ ) ;

/* Variables and functions */
 scalar_t__ EOF ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  check_attr (char const*,struct attr_check*,int,char*) ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  maybe_flush_or_die (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ nul_term_line ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strbuf_getline_lf (struct strbuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ strbuf_getline_nul (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_swap (struct strbuf*,struct strbuf*) ; 
 scalar_t__ unquote_c_style (struct strbuf*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void check_attr_stdin_paths(const char *prefix,
				   struct attr_check *check,
				   int collect_all)
{
	struct strbuf buf = STRBUF_INIT;
	struct strbuf unquoted = STRBUF_INIT;
	strbuf_getline_fn getline_fn;

	getline_fn = nul_term_line ? strbuf_getline_nul : strbuf_getline_lf;
	while (getline_fn(&buf, stdin) != EOF) {
		if (!nul_term_line && buf.buf[0] == '"') {
			strbuf_reset(&unquoted);
			if (unquote_c_style(&unquoted, buf.buf, NULL))
				die("line is badly quoted");
			strbuf_swap(&buf, &unquoted);
		}
		check_attr(prefix, check, collect_all, buf.buf);
		maybe_flush_or_die(stdout, "attribute to stdout");
	}
	strbuf_release(&buf);
	strbuf_release(&unquoted);
}