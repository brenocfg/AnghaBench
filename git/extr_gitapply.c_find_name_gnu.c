#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct strbuf {char* buf; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct apply_state {TYPE_1__ root; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 char* squash_slash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_insert (struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_remove (struct strbuf*,int /*<<< orphan*/ ,int) ; 
 char* strchr (char*,char) ; 
 scalar_t__ unquote_c_style (struct strbuf*,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *find_name_gnu(struct apply_state *state,
			   const char *line,
			   int p_value)
{
	struct strbuf name = STRBUF_INIT;
	char *cp;

	/*
	 * Proposed "new-style" GNU patch/diff format; see
	 * http://marc.info/?l=git&m=112927316408690&w=2
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
	if (state->root.len)
		strbuf_insert(&name, 0, state->root.buf, state->root.len);
	return squash_slash(strbuf_detach(&name, NULL));
}