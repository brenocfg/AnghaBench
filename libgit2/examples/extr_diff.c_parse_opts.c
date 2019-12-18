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
struct TYPE_3__ {int id_abbrev; int /*<<< orphan*/  new_prefix; int /*<<< orphan*/  old_prefix; int /*<<< orphan*/  interhunk_lines; int /*<<< orphan*/  context_lines; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int rename_threshold; int copy_threshold; int /*<<< orphan*/  flags; } ;
struct opts {char const* treeish1; char const* treeish2; scalar_t__ cache; scalar_t__ no_index; int color; int /*<<< orphan*/  dir; TYPE_1__ diffopts; TYPE_2__ findopts; int /*<<< orphan*/  output; void* format; } ;
struct args_info {int pos; } ;

/* Variables and functions */
 struct args_info ARGS_INFO_INIT ; 
 scalar_t__ CACHE_NONE ; 
 scalar_t__ CACHE_ONLY ; 
 int /*<<< orphan*/  GIT_DIFF_FIND_COPIES ; 
 int /*<<< orphan*/  GIT_DIFF_FIND_COPIES_FROM_UNMODIFIED ; 
 int /*<<< orphan*/  GIT_DIFF_FIND_RENAMES ; 
 int /*<<< orphan*/  GIT_DIFF_FIND_REWRITES ; 
 int /*<<< orphan*/  GIT_DIFF_FORCE_TEXT ; 
 void* GIT_DIFF_FORMAT_NAME_ONLY ; 
 void* GIT_DIFF_FORMAT_NAME_STATUS ; 
 void* GIT_DIFF_FORMAT_PATCH ; 
 void* GIT_DIFF_FORMAT_RAW ; 
 int /*<<< orphan*/  GIT_DIFF_IGNORE_WHITESPACE ; 
 int /*<<< orphan*/  GIT_DIFF_IGNORE_WHITESPACE_CHANGE ; 
 int /*<<< orphan*/  GIT_DIFF_IGNORE_WHITESPACE_EOL ; 
 int /*<<< orphan*/  GIT_DIFF_INCLUDE_IGNORED ; 
 int /*<<< orphan*/  GIT_DIFF_INCLUDE_UNTRACKED ; 
 int /*<<< orphan*/  GIT_DIFF_MINIMAL ; 
 int /*<<< orphan*/  GIT_DIFF_PATIENCE ; 
 int /*<<< orphan*/  GIT_DIFF_REVERSE ; 
 int /*<<< orphan*/  OUTPUT_DIFF ; 
 int /*<<< orphan*/  OUTPUT_NUMSTAT ; 
 int /*<<< orphan*/  OUTPUT_SHORTSTAT ; 
 int /*<<< orphan*/  OUTPUT_STAT ; 
 int /*<<< orphan*/  OUTPUT_SUMMARY ; 
 scalar_t__ is_prefixed (char const*,char*) ; 
 int /*<<< orphan*/  match_str_arg (int /*<<< orphan*/ *,struct args_info*,char*) ; 
 scalar_t__ match_uint16_arg (int*,struct args_info*,char*) ; 
 int /*<<< orphan*/  match_uint32_arg (int /*<<< orphan*/ *,struct args_info*,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  usage (char*,char const*) ; 

__attribute__((used)) static void parse_opts(struct opts *o, int argc, char *argv[])
{
	struct args_info args = ARGS_INFO_INIT;


	for (args.pos = 1; args.pos < argc; ++args.pos) {
		const char *a = argv[args.pos];

		if (a[0] != '-') {
			if (o->treeish1 == NULL)
				o->treeish1 = a;
			else if (o->treeish2 == NULL)
				o->treeish2 = a;
			else
				usage("Only one or two tree identifiers can be provided", NULL);
		}
		else if (!strcmp(a, "-p") || !strcmp(a, "-u") ||
				 !strcmp(a, "--patch")) {
			o->output |= OUTPUT_DIFF;
			o->format = GIT_DIFF_FORMAT_PATCH;
		}
		else if (!strcmp(a, "--cached")) {
			o->cache = CACHE_ONLY;
			if (o->no_index >= 0) usage("--cached and --no-index are incompatible", NULL);
		} else if (!strcmp(a, "--nocache"))
			o->cache = CACHE_NONE;
		else if (!strcmp(a, "--name-only") || !strcmp(a, "--format=name"))
			o->format = GIT_DIFF_FORMAT_NAME_ONLY;
		else if (!strcmp(a, "--name-status") ||
				!strcmp(a, "--format=name-status"))
			o->format = GIT_DIFF_FORMAT_NAME_STATUS;
		else if (!strcmp(a, "--raw") || !strcmp(a, "--format=raw"))
			o->format = GIT_DIFF_FORMAT_RAW;
		else if (!strcmp(a, "--format=diff-index")) {
			o->format = GIT_DIFF_FORMAT_RAW;
			o->diffopts.id_abbrev = 40;
		}
		else if (!strcmp(a, "--no-index")) {
			o->no_index = 0;
			if (o->cache == CACHE_ONLY) usage("--cached and --no-index are incompatible", NULL);
		} else if (!strcmp(a, "--color"))
			o->color = 0;
		else if (!strcmp(a, "--no-color"))
			o->color = -1;
		else if (!strcmp(a, "-R"))
			o->diffopts.flags |= GIT_DIFF_REVERSE;
		else if (!strcmp(a, "-a") || !strcmp(a, "--text"))
			o->diffopts.flags |= GIT_DIFF_FORCE_TEXT;
		else if (!strcmp(a, "--ignore-space-at-eol"))
			o->diffopts.flags |= GIT_DIFF_IGNORE_WHITESPACE_EOL;
		else if (!strcmp(a, "-b") || !strcmp(a, "--ignore-space-change"))
			o->diffopts.flags |= GIT_DIFF_IGNORE_WHITESPACE_CHANGE;
		else if (!strcmp(a, "-w") || !strcmp(a, "--ignore-all-space"))
			o->diffopts.flags |= GIT_DIFF_IGNORE_WHITESPACE;
		else if (!strcmp(a, "--ignored"))
			o->diffopts.flags |= GIT_DIFF_INCLUDE_IGNORED;
		else if (!strcmp(a, "--untracked"))
			o->diffopts.flags |= GIT_DIFF_INCLUDE_UNTRACKED;
		else if (!strcmp(a, "--patience"))
			o->diffopts.flags |= GIT_DIFF_PATIENCE;
		else if (!strcmp(a, "--minimal"))
			o->diffopts.flags |= GIT_DIFF_MINIMAL;
		else if (!strcmp(a, "--stat"))
			o->output |= OUTPUT_STAT;
		else if (!strcmp(a, "--numstat"))
			o->output |= OUTPUT_NUMSTAT;
		else if (!strcmp(a, "--shortstat"))
			o->output |= OUTPUT_SHORTSTAT;
		else if (!strcmp(a, "--summary"))
			o->output |= OUTPUT_SUMMARY;
		else if (match_uint16_arg(
				&o->findopts.rename_threshold, &args, "-M") ||
			match_uint16_arg(
				&o->findopts.rename_threshold, &args, "--find-renames"))
			o->findopts.flags |= GIT_DIFF_FIND_RENAMES;
		else if (match_uint16_arg(
				&o->findopts.copy_threshold, &args, "-C") ||
			match_uint16_arg(
				&o->findopts.copy_threshold, &args, "--find-copies"))
			o->findopts.flags |= GIT_DIFF_FIND_COPIES;
		else if (!strcmp(a, "--find-copies-harder"))
			o->findopts.flags |= GIT_DIFF_FIND_COPIES_FROM_UNMODIFIED;
		else if (is_prefixed(a, "-B") || is_prefixed(a, "--break-rewrites"))
			/* TODO: parse thresholds */
			o->findopts.flags |= GIT_DIFF_FIND_REWRITES;
		else if (!match_uint32_arg(
				&o->diffopts.context_lines, &args, "-U") &&
			!match_uint32_arg(
				&o->diffopts.context_lines, &args, "--unified") &&
			!match_uint32_arg(
				&o->diffopts.interhunk_lines, &args, "--inter-hunk-context") &&
			!match_uint16_arg(
				&o->diffopts.id_abbrev, &args, "--abbrev") &&
			!match_str_arg(&o->diffopts.old_prefix, &args, "--src-prefix") &&
			!match_str_arg(&o->diffopts.new_prefix, &args, "--dst-prefix") &&
			!match_str_arg(&o->dir, &args, "--git-dir"))
			usage("Unknown command line argument", a);
	}
}