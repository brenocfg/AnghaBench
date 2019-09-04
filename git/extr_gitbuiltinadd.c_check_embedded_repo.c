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
 scalar_t__ advice_add_embedded_repo ; 
 int /*<<< orphan*/  advise (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  embedded_advice ; 
 int /*<<< orphan*/  ends_with (char const*,char*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_strip_suffix (struct strbuf*,char*) ; 
 int /*<<< orphan*/  warn_on_embedded_repo ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void check_embedded_repo(const char *path)
{
	struct strbuf name = STRBUF_INIT;

	if (!warn_on_embedded_repo)
		return;
	if (!ends_with(path, "/"))
		return;

	/* Drop trailing slash for aesthetics */
	strbuf_addstr(&name, path);
	strbuf_strip_suffix(&name, "/");

	warning(_("adding embedded git repository: %s"), name.buf);
	if (advice_add_embedded_repo) {
		advise(embedded_advice, name.buf, name.buf);
		/* there may be multiple entries; advise only once */
		advice_add_embedded_repo = 0;
	}

	strbuf_release(&name);
}