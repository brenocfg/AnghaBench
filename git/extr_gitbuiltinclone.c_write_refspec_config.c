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
struct strbuf {int /*<<< orphan*/  buf; scalar_t__ len; } ;
struct ref {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  git_config_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_config_set_multivar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  option_bare ; 
 scalar_t__ option_branch ; 
 scalar_t__ option_mirror ; 
 int /*<<< orphan*/  option_origin ; 
 scalar_t__ option_single_branch ; 
 int /*<<< orphan*/  skip_prefix (char const*,char*,char const**) ; 
 scalar_t__ starts_with (char*,char*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*,...) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 

__attribute__((used)) static void write_refspec_config(const char *src_ref_prefix,
		const struct ref *our_head_points_at,
		const struct ref *remote_head_points_at,
		struct strbuf *branch_top)
{
	struct strbuf key = STRBUF_INIT;
	struct strbuf value = STRBUF_INIT;

	if (option_mirror || !option_bare) {
		if (option_single_branch && !option_mirror) {
			if (option_branch) {
				if (starts_with(our_head_points_at->name, "refs/tags/"))
					strbuf_addf(&value, "+%s:%s", our_head_points_at->name,
						our_head_points_at->name);
				else
					strbuf_addf(&value, "+%s:%s%s", our_head_points_at->name,
						branch_top->buf, option_branch);
			} else if (remote_head_points_at) {
				const char *head = remote_head_points_at->name;
				if (!skip_prefix(head, "refs/heads/", &head))
					BUG("remote HEAD points at non-head?");

				strbuf_addf(&value, "+%s:%s%s", remote_head_points_at->name,
						branch_top->buf, head);
			}
			/*
			 * otherwise, the next "git fetch" will
			 * simply fetch from HEAD without updating
			 * any remote-tracking branch, which is what
			 * we want.
			 */
		} else {
			strbuf_addf(&value, "+%s*:%s*", src_ref_prefix, branch_top->buf);
		}
		/* Configure the remote */
		if (value.len) {
			strbuf_addf(&key, "remote.%s.fetch", option_origin);
			git_config_set_multivar(key.buf, value.buf, "^$", 0);
			strbuf_reset(&key);

			if (option_mirror) {
				strbuf_addf(&key, "remote.%s.mirror", option_origin);
				git_config_set(key.buf, "true");
				strbuf_reset(&key);
			}
		}
	}

	strbuf_release(&key);
	strbuf_release(&value);
}