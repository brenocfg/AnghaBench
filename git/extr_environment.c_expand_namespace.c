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

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ check_refname_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 char* strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_list_free (struct strbuf**) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 struct strbuf** strbuf_split (struct strbuf*,char) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static char *expand_namespace(const char *raw_namespace)
{
	struct strbuf buf = STRBUF_INIT;
	struct strbuf **components, **c;

	if (!raw_namespace || !*raw_namespace)
		return xstrdup("");

	strbuf_addstr(&buf, raw_namespace);
	components = strbuf_split(&buf, '/');
	strbuf_reset(&buf);
	for (c = components; *c; c++)
		if (strcmp((*c)->buf, "/") != 0)
			strbuf_addf(&buf, "refs/namespaces/%s", (*c)->buf);
	strbuf_list_free(components);
	if (check_refname_format(buf.buf, 0))
		die(_("bad git namespace path \"%s\""), raw_namespace);
	strbuf_addch(&buf, '/');
	return strbuf_detach(&buf, NULL);
}