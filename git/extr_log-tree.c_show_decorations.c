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
struct strbuf {int /*<<< orphan*/  buf; } ;
struct TYPE_2__ {int /*<<< orphan*/  file; int /*<<< orphan*/  use_color; } ;
struct rev_info {TYPE_1__ diffopt; int /*<<< orphan*/  show_decorations; scalar_t__ sources; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  format_decorations (struct strbuf*,struct commit*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char** revision_sources_peek (scalar_t__,struct commit*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

void show_decorations(struct rev_info *opt, struct commit *commit)
{
	struct strbuf sb = STRBUF_INIT;

	if (opt->sources) {
		char **slot = revision_sources_peek(opt->sources, commit);

		if (slot && *slot)
			fprintf(opt->diffopt.file, "\t%s", *slot);
	}
	if (!opt->show_decorations)
		return;
	format_decorations(&sb, commit, opt->diffopt.use_color);
	fputs(sb.buf, opt->diffopt.file);
	strbuf_release(&sb);
}