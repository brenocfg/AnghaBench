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
struct strbuf {char const* buf; scalar_t__ len; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int chop_last_dir (char**,int) ; 
 scalar_t__ ends_with (char const*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ is_absolute_path (char*) ; 
 scalar_t__ is_dir_sep (char) ; 
 scalar_t__ starts_with_dot_dot_slash (char const*) ; 
 scalar_t__ starts_with_dot_slash (char const*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*,...) ; 
 char* strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,scalar_t__) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  url_is_local_not_ssh (char*) ; 
 char* xstrdup (char const*) ; 

__attribute__((used)) static char *relative_url(const char *remote_url,
				const char *url,
				const char *up_path)
{
	int is_relative = 0;
	int colonsep = 0;
	char *out;
	char *remoteurl = xstrdup(remote_url);
	struct strbuf sb = STRBUF_INIT;
	size_t len = strlen(remoteurl);

	if (is_dir_sep(remoteurl[len-1]))
		remoteurl[len-1] = '\0';

	if (!url_is_local_not_ssh(remoteurl) || is_absolute_path(remoteurl))
		is_relative = 0;
	else {
		is_relative = 1;
		/*
		 * Prepend a './' to ensure all relative
		 * remoteurls start with './' or '../'
		 */
		if (!starts_with_dot_slash(remoteurl) &&
		    !starts_with_dot_dot_slash(remoteurl)) {
			strbuf_reset(&sb);
			strbuf_addf(&sb, "./%s", remoteurl);
			free(remoteurl);
			remoteurl = strbuf_detach(&sb, NULL);
		}
	}
	/*
	 * When the url starts with '../', remove that and the
	 * last directory in remoteurl.
	 */
	while (url) {
		if (starts_with_dot_dot_slash(url)) {
			url += 3;
			colonsep |= chop_last_dir(&remoteurl, is_relative);
		} else if (starts_with_dot_slash(url))
			url += 2;
		else
			break;
	}
	strbuf_reset(&sb);
	strbuf_addf(&sb, "%s%s%s", remoteurl, colonsep ? ":" : "/", url);
	if (ends_with(url, "/"))
		strbuf_setlen(&sb, sb.len - 1);
	free(remoteurl);

	if (starts_with_dot_slash(sb.buf))
		out = xstrdup(sb.buf + 2);
	else
		out = xstrdup(sb.buf);
	strbuf_reset(&sb);

	if (!up_path || !is_relative)
		return out;

	strbuf_addf(&sb, "%s%s", up_path, out);
	free(out);
	return strbuf_detach(&sb, NULL);
}