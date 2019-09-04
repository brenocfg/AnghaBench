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
struct strbuf {int /*<<< orphan*/  buf; } ;
struct TYPE_4__ {int nr; TYPE_1__* items; } ;
struct ref_states {TYPE_2__ heads; } ;
struct option {int dummy; } ;
typedef  int /*<<< orphan*/  states ;
struct TYPE_3__ {char* string; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_HEAD_NAMES ; 
 int /*<<< orphan*/  N_ (char*) ; 
 struct option OPT_BOOL (char,char*,int*,int /*<<< orphan*/ ) ; 
 struct option OPT_END () ; 
 int /*<<< orphan*/  REF_NO_DEREF ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  builtin_remote_sethead_usage ; 
 scalar_t__ create_symref (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ delete_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int error (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  free_remote_ref_states (struct ref_states*) ; 
 int /*<<< orphan*/  get_remote_ref_states (char const*,struct ref_states*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ref_states*,int /*<<< orphan*/ ,int) ; 
 int parse_options (int,char const**,int /*<<< orphan*/ *,struct option*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char const*,char*) ; 
 int /*<<< orphan*/  ref_exists (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*,...) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  usage_with_options (int /*<<< orphan*/ ,struct option*) ; 
 char* xstrdup (char const*) ; 

__attribute__((used)) static int set_head(int argc, const char **argv)
{
	int i, opt_a = 0, opt_d = 0, result = 0;
	struct strbuf buf = STRBUF_INIT, buf2 = STRBUF_INIT;
	char *head_name = NULL;

	struct option options[] = {
		OPT_BOOL('a', "auto", &opt_a,
			 N_("set refs/remotes/<name>/HEAD according to remote")),
		OPT_BOOL('d', "delete", &opt_d,
			 N_("delete refs/remotes/<name>/HEAD")),
		OPT_END()
	};
	argc = parse_options(argc, argv, NULL, options, builtin_remote_sethead_usage,
			     0);
	if (argc)
		strbuf_addf(&buf, "refs/remotes/%s/HEAD", argv[0]);

	if (!opt_a && !opt_d && argc == 2) {
		head_name = xstrdup(argv[1]);
	} else if (opt_a && !opt_d && argc == 1) {
		struct ref_states states;
		memset(&states, 0, sizeof(states));
		get_remote_ref_states(argv[0], &states, GET_HEAD_NAMES);
		if (!states.heads.nr)
			result |= error(_("Cannot determine remote HEAD"));
		else if (states.heads.nr > 1) {
			result |= error(_("Multiple remote HEAD branches. "
					  "Please choose one explicitly with:"));
			for (i = 0; i < states.heads.nr; i++)
				fprintf(stderr, "  git remote set-head %s %s\n",
					argv[0], states.heads.items[i].string);
		} else
			head_name = xstrdup(states.heads.items[0].string);
		free_remote_ref_states(&states);
	} else if (opt_d && !opt_a && argc == 1) {
		if (delete_ref(NULL, buf.buf, NULL, REF_NO_DEREF))
			result |= error(_("Could not delete %s"), buf.buf);
	} else
		usage_with_options(builtin_remote_sethead_usage, options);

	if (head_name) {
		strbuf_addf(&buf2, "refs/remotes/%s/%s", argv[0], head_name);
		/* make sure it's valid */
		if (!ref_exists(buf2.buf))
			result |= error(_("Not a valid ref: %s"), buf2.buf);
		else if (create_symref(buf.buf, buf2.buf, "remote set-head"))
			result |= error(_("Could not setup %s"), buf.buf);
		if (opt_a)
			printf("%s/HEAD set to %s\n", argv[0], head_name);
		free(head_name);
	}

	strbuf_release(&buf);
	strbuf_release(&buf2);
	return result;
}