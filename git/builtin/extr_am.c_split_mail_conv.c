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
struct am_state {int cur; int last; int /*<<< orphan*/  prec; int /*<<< orphan*/  dir; } ;
typedef  int (* mail_conv_fn ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int error (int /*<<< orphan*/ ,char const*) ; 
 int error_errno (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 char* mkpath (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int split_mail_conv(mail_conv_fn fn, struct am_state *state,
			const char **paths, int keep_cr)
{
	static const char *stdin_only[] = {"-", NULL};
	int i;

	if (!*paths)
		paths = stdin_only;

	for (i = 0; *paths; paths++, i++) {
		FILE *in, *out;
		const char *mail;
		int ret;

		if (!strcmp(*paths, "-"))
			in = stdin;
		else
			in = fopen(*paths, "r");

		if (!in)
			return error_errno(_("could not open '%s' for reading"),
					   *paths);

		mail = mkpath("%s/%0*d", state->dir, state->prec, i + 1);

		out = fopen(mail, "w");
		if (!out) {
			if (in != stdin)
				fclose(in);
			return error_errno(_("could not open '%s' for writing"),
					   mail);
		}

		ret = fn(out, in, keep_cr);

		fclose(out);
		if (in != stdin)
			fclose(in);

		if (ret)
			return error(_("could not parse patch '%s'"), *paths);
	}

	state->cur = 1;
	state->last = i;
	return 0;
}