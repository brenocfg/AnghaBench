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
struct TYPE_2__ {int /*<<< orphan*/  oid; } ;
struct commit {TYPE_1__ object; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CMIT_FMT_ONELINE ; 
 struct strbuf STRBUF_INIT ; 
 char* find_unique_abbrev (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char,char*,...) ; 
 int /*<<< orphan*/  pp_commit_easy (int /*<<< orphan*/ ,struct commit*,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void print_commit(char sign, struct commit *commit, int verbose,
			 int abbrev, FILE *file)
{
	if (!verbose) {
		fprintf(file, "%c %s\n", sign,
		       find_unique_abbrev(&commit->object.oid, abbrev));
	} else {
		struct strbuf buf = STRBUF_INIT;
		pp_commit_easy(CMIT_FMT_ONELINE, commit, &buf);
		fprintf(file, "%c %s %s\n", sign,
		       find_unique_abbrev(&commit->object.oid, abbrev),
		       buf.buf);
		strbuf_release(&buf);
	}
}