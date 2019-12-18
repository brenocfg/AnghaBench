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
struct gctl_req {int dummy; } ;
struct g_option {int go_type; char* go_val; int /*<<< orphan*/  go_char; int /*<<< orphan*/ * go_name; } ;
struct g_command {int gc_flags; struct g_option* gc_options; } ;
typedef  int /*<<< orphan*/  opts ;
typedef  int /*<<< orphan*/  argname ;

/* Variables and functions */
 int G_FLAG_VERBOSE ; 
 int /*<<< orphan*/  G_OPT_DONE (struct g_option*) ; 
 scalar_t__ G_OPT_ISDONE (struct g_option*) ; 
 int /*<<< orphan*/  G_OPT_ISMULTI (struct g_option*) ; 
 scalar_t__ G_OPT_TYPE (struct g_option*) ; 
 scalar_t__ G_TYPE_BOOL ; 
 int G_TYPE_MASK ; 
 int G_TYPE_MULTI ; 
 char* G_VAL_OPTIONAL ; 
 int /*<<< orphan*/  assert (int) ; 
 struct g_option* find_option (struct g_command*,int) ; 
 int /*<<< orphan*/  gctl_ro_param (struct gctl_req*,char*,int,...) ; 
 int getopt (int,char**,char*) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  set_option (struct gctl_req*,struct g_option*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 int /*<<< orphan*/  strlcatf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 
 int verbose ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
parse_arguments(struct g_command *cmd, struct gctl_req *req, int *argc,
    char ***argv)
{
	struct g_option *opt;
	char opts[64];
	unsigned i;
	int ch;

	*opts = '\0';
	if ((cmd->gc_flags & G_FLAG_VERBOSE) != 0)
		strlcat(opts, "v", sizeof(opts));
	for (i = 0; ; i++) {
		opt = &cmd->gc_options[i];
		if (opt->go_name == NULL)
			break;
		assert(G_OPT_TYPE(opt) != 0);
		assert((opt->go_type & ~(G_TYPE_MASK | G_TYPE_MULTI)) == 0);
		/* Multiple bool arguments makes no sense. */
		assert(G_OPT_TYPE(opt) != G_TYPE_BOOL ||
		    (opt->go_type & G_TYPE_MULTI) == 0);
		strlcatf(opts, sizeof(opts), "%c", opt->go_char);
		if (G_OPT_TYPE(opt) != G_TYPE_BOOL)
			strlcat(opts, ":", sizeof(opts));
	}

	/*
	 * Add specified arguments.
	 */
	while ((ch = getopt(*argc, *argv, opts)) != -1) {
		/* Standard (not passed to kernel) options. */
		switch (ch) {
		case 'v':
			verbose = 1;
			continue;
		}
		/* Options passed to kernel. */
		opt = find_option(cmd, ch);
		if (opt == NULL)
			usage();
		if (!G_OPT_ISMULTI(opt) && G_OPT_ISDONE(opt)) {
			warnx("Option '%c' specified twice.", opt->go_char);
			usage();
		}
		G_OPT_DONE(opt);

		if (G_OPT_TYPE(opt) == G_TYPE_BOOL)
			set_option(req, opt, "1");
		else
			set_option(req, opt, optarg);
	}
	*argc -= optind;
	*argv += optind;

	/*
	 * Add not specified arguments, but with default values.
	 */
	for (i = 0; ; i++) {
		opt = &cmd->gc_options[i];
		if (opt->go_name == NULL)
			break;
		if (G_OPT_ISDONE(opt))
			continue;

		if (G_OPT_TYPE(opt) == G_TYPE_BOOL) {
			assert(opt->go_val == NULL);
			set_option(req, opt, "0");
		} else {
			if (opt->go_val == NULL) {
				warnx("Option '%c' not specified.",
				    opt->go_char);
				usage();
			} else if (opt->go_val == G_VAL_OPTIONAL) {
				/* add nothing. */
			} else {
				set_option(req, opt, opt->go_val);
			}
		}
	}

	/*
	 * Add rest of given arguments.
	 */
	gctl_ro_param(req, "nargs", sizeof(int), argc);
	for (i = 0; i < (unsigned)*argc; i++) {
		char argname[16];

		snprintf(argname, sizeof(argname), "arg%u", i);
		gctl_ro_param(req, argname, -1, (*argv)[i]);
	}
}