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
struct commit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct commit* lookup_commit_reference_by_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int,char const*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_splice (struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static struct commit *lookup_label(const char *label, int len,
				   struct strbuf *buf)
{
	struct commit *commit;

	strbuf_reset(buf);
	strbuf_addf(buf, "refs/rewritten/%.*s", len, label);
	commit = lookup_commit_reference_by_name(buf->buf);
	if (!commit) {
		/* fall back to non-rewritten ref or commit */
		strbuf_splice(buf, 0, strlen("refs/rewritten/"), "", 0);
		commit = lookup_commit_reference_by_name(buf->buf);
	}

	if (!commit)
		error(_("could not resolve '%s'"), buf->buf);

	return commit;
}