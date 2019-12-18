#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct strbuf {char* buf; } ;
struct pretty_print_context {int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {int /*<<< orphan*/  oid; } ;
struct commit {TYPE_1__ object; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  format_commit_message (struct commit*,char*,struct strbuf*,struct pretty_print_context*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 char* xstrfmt (char*,char const*) ; 

__attribute__((used)) static void log_commit(FILE *fp, char *fmt, const char *state,
		       struct commit *commit)
{
	struct pretty_print_context pp = {0};
	struct strbuf commit_msg = STRBUF_INIT;
	char *label = xstrfmt(fmt, state);

	format_commit_message(commit, "%s", &commit_msg, &pp);

	fprintf(fp, "# %s: [%s] %s\n", label, oid_to_hex(&commit->object.oid),
		commit_msg.buf);

	strbuf_release(&commit_msg);
	free(label);
}