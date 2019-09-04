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
struct argv_array {int /*<<< orphan*/  argv; } ;
struct am_state {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 struct argv_array ARGV_ARRAY_INIT ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  argv_array_clear (struct argv_array*) ; 
 int /*<<< orphan*/  argv_array_push (struct argv_array*,int /*<<< orphan*/ ) ; 
 char* dirname (char*) ; 
 int error (int /*<<< orphan*/ ) ; 
 int error_errno (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  mkpath (char*,char const*,char*) ; 
 int split_mail_conv (int /*<<< orphan*/ ,struct am_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stgit_patch_to_mail ; 
 int /*<<< orphan*/  strbuf_getline_lf (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 char* xstrdup (char const*) ; 

__attribute__((used)) static int split_mail_stgit_series(struct am_state *state, const char **paths,
					int keep_cr)
{
	const char *series_dir;
	char *series_dir_buf;
	FILE *fp;
	struct argv_array patches = ARGV_ARRAY_INIT;
	struct strbuf sb = STRBUF_INIT;
	int ret;

	if (!paths[0] || paths[1])
		return error(_("Only one StGIT patch series can be applied at once"));

	series_dir_buf = xstrdup(*paths);
	series_dir = dirname(series_dir_buf);

	fp = fopen(*paths, "r");
	if (!fp)
		return error_errno(_("could not open '%s' for reading"), *paths);

	while (!strbuf_getline_lf(&sb, fp)) {
		if (*sb.buf == '#')
			continue; /* skip comment lines */

		argv_array_push(&patches, mkpath("%s/%s", series_dir, sb.buf));
	}

	fclose(fp);
	strbuf_release(&sb);
	free(series_dir_buf);

	ret = split_mail_conv(stgit_patch_to_mail, state, patches.argv, keep_cr);

	argv_array_clear(&patches);
	return ret;
}