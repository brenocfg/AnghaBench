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
struct strbuf {char* buf; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 char* squash_slash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_insert (struct strbuf*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_remove (struct strbuf*,int /*<<< orphan*/ ,int) ; 
 char* strchr (char*,char) ; 
 scalar_t__ unquote_c_style (struct strbuf*,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *find_name_gnu(struct strbuf *root,
			   const char *line,
			   int p_value)
{
	struct strbuf name = STRBUF_INIT;
	char *cp;

	/*
	 * Proposed "new-style" GNU patch/diff format; see
	 * https://public-inbox.org/git/7vll0wvb2a.fsf@assigned-by-dhcp.cox.net/
	 */
	if (unquote_c_style(&name, line, NULL)) {
		strbuf_release(&name);
		return NULL;
	}

	for (cp = name.buf; p_value; p_value--) {
		cp = strchr(cp, '/');
		if (!cp) {
			strbuf_release(&name);
			return NULL;
		}
		cp++;
	}

	strbuf_remove(&name, 0, cp - name.buf);
	if (root->len)
		strbuf_insert(&name, 0, root->buf, root->len);
	return squash_slash(strbuf_detach(&name, NULL));
}