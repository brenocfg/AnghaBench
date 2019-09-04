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
struct strbuf {size_t len; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip_prefix (char const*,int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strip_suffix_mem (int /*<<< orphan*/ ,size_t*,char const*) ; 

__attribute__((used)) static int update_url_from_redirect(struct strbuf *base,
				    const char *asked,
				    const struct strbuf *got)
{
	const char *tail;
	size_t new_len;

	if (!strcmp(asked, got->buf))
		return 0;

	if (!skip_prefix(asked, base->buf, &tail))
		BUG("update_url_from_redirect: %s is not a superset of %s",
		    asked, base->buf);

	new_len = got->len;
	if (!strip_suffix_mem(got->buf, &new_len, tail))
		die(_("unable to update url base from redirection:\n"
		      "  asked for: %s\n"
		      "   redirect: %s"),
		    asked, got->buf);

	strbuf_reset(base);
	strbuf_add(base, got->buf, new_len);

	return 1;
}