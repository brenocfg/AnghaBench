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
struct remote {char** pushurl; int pushurl_nr; char** url; int url_nr; } ;
struct option {int dummy; } ;
typedef  int /*<<< orphan*/  regex_t ;

/* Variables and functions */
 int /*<<< orphan*/  N_ (char*) ; 
 struct option OPT_BOOL (char,char*,int*,int /*<<< orphan*/ ) ; 
 struct option OPT_END () ; 
 int /*<<< orphan*/  PARSE_OPT_KEEP_ARGV0 ; 
 int /*<<< orphan*/  REG_EXTENDED ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  builtin_remote_seturl_usage ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  git_config_set (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_config_set_multivar (int /*<<< orphan*/ ,char const*,char const*,int) ; 
 int parse_options (int,char const**,int /*<<< orphan*/ *,struct option*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ regcomp (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regexec (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regfree (int /*<<< orphan*/ *) ; 
 struct remote* remote_get (char const*) ; 
 int /*<<< orphan*/  remote_is_configured (struct remote*,int) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  usage_with_options (int /*<<< orphan*/ ,struct option*) ; 

__attribute__((used)) static int set_url(int argc, const char **argv)
{
	int i, push_mode = 0, add_mode = 0, delete_mode = 0;
	int matches = 0, negative_matches = 0;
	const char *remotename = NULL;
	const char *newurl = NULL;
	const char *oldurl = NULL;
	struct remote *remote;
	regex_t old_regex;
	const char **urlset;
	int urlset_nr;
	struct strbuf name_buf = STRBUF_INIT;
	struct option options[] = {
		OPT_BOOL('\0', "push", &push_mode,
			 N_("manipulate push URLs")),
		OPT_BOOL('\0', "add", &add_mode,
			 N_("add URL")),
		OPT_BOOL('\0', "delete", &delete_mode,
			    N_("delete URLs")),
		OPT_END()
	};
	argc = parse_options(argc, argv, NULL, options, builtin_remote_seturl_usage,
			     PARSE_OPT_KEEP_ARGV0);

	if (add_mode && delete_mode)
		die(_("--add --delete doesn't make sense"));

	if (argc < 3 || argc > 4 || ((add_mode || delete_mode) && argc != 3))
		usage_with_options(builtin_remote_seturl_usage, options);

	remotename = argv[1];
	newurl = argv[2];
	if (argc > 3)
		oldurl = argv[3];

	if (delete_mode)
		oldurl = newurl;

	remote = remote_get(remotename);
	if (!remote_is_configured(remote, 1))
		die(_("No such remote '%s'"), remotename);

	if (push_mode) {
		strbuf_addf(&name_buf, "remote.%s.pushurl", remotename);
		urlset = remote->pushurl;
		urlset_nr = remote->pushurl_nr;
	} else {
		strbuf_addf(&name_buf, "remote.%s.url", remotename);
		urlset = remote->url;
		urlset_nr = remote->url_nr;
	}

	/* Special cases that add new entry. */
	if ((!oldurl && !delete_mode) || add_mode) {
		if (add_mode)
			git_config_set_multivar(name_buf.buf, newurl,
						       "^$", 0);
		else
			git_config_set(name_buf.buf, newurl);
		goto out;
	}

	/* Old URL specified. Demand that one matches. */
	if (regcomp(&old_regex, oldurl, REG_EXTENDED))
		die(_("Invalid old URL pattern: %s"), oldurl);

	for (i = 0; i < urlset_nr; i++)
		if (!regexec(&old_regex, urlset[i], 0, NULL, 0))
			matches++;
		else
			negative_matches++;
	if (!delete_mode && !matches)
		die(_("No such URL found: %s"), oldurl);
	if (delete_mode && !negative_matches && !push_mode)
		die(_("Will not delete all non-push URLs"));

	regfree(&old_regex);

	if (!delete_mode)
		git_config_set_multivar(name_buf.buf, newurl, oldurl, 0);
	else
		git_config_set_multivar(name_buf.buf, NULL, oldurl, 1);
out:
	strbuf_release(&name_buf);
	return 0;
}