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
struct strbuf {int len; int /*<<< orphan*/  buf; } ;
struct index_state {int dummy; } ;
struct attr_stack {int originlen; int /*<<< orphan*/  origin; struct attr_stack* prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GITATTRIBUTES_FILE ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  attr_stack_free (struct attr_stack*) ; 
 int /*<<< orphan*/  bootstrap_attr_stack (struct index_state const*,struct attr_stack**) ; 
 int /*<<< orphan*/  debug_pop (struct attr_stack*) ; 
 scalar_t__ is_dir_sep (char const) ; 
 int /*<<< orphan*/  push_stack (struct attr_stack**,struct attr_stack*,char*,size_t) ; 
 struct attr_stack* read_attr (struct index_state const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char const*,size_t) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,size_t) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char const*,int) ; 
 char* xstrdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void prepare_attr_stack(const struct index_state *istate,
			       const char *path, int dirlen,
			       struct attr_stack **stack)
{
	struct attr_stack *info;
	struct strbuf pathbuf = STRBUF_INIT;

	/*
	 * At the bottom of the attribute stack is the built-in
	 * set of attribute definitions, followed by the contents
	 * of $(prefix)/etc/gitattributes and a file specified by
	 * core.attributesfile.  Then, contents from
	 * .gitattributes files from directories closer to the
	 * root to the ones in deeper directories are pushed
	 * to the stack.  Finally, at the very top of the stack
	 * we always keep the contents of $GIT_DIR/info/attributes.
	 *
	 * When checking, we use entries from near the top of the
	 * stack, preferring $GIT_DIR/info/attributes, then
	 * .gitattributes in deeper directories to shallower ones,
	 * and finally use the built-in set as the default.
	 */
	bootstrap_attr_stack(istate, stack);

	/*
	 * Pop the "info" one that is always at the top of the stack.
	 */
	info = *stack;
	*stack = info->prev;

	/*
	 * Pop the ones from directories that are not the prefix of
	 * the path we are checking. Break out of the loop when we see
	 * the root one (whose origin is an empty string "") or the builtin
	 * one (whose origin is NULL) without popping it.
	 */
	while ((*stack)->origin) {
		int namelen = (*stack)->originlen;
		struct attr_stack *elem;

		elem = *stack;
		if (namelen <= dirlen &&
		    !strncmp(elem->origin, path, namelen) &&
		    (!namelen || path[namelen] == '/'))
			break;

		debug_pop(elem);
		*stack = elem->prev;
		attr_stack_free(elem);
	}

	/*
	 * bootstrap_attr_stack() should have added, and the
	 * above loop should have stopped before popping, the
	 * root element whose attr_stack->origin is set to an
	 * empty string.
	 */
	assert((*stack)->origin);

	strbuf_addstr(&pathbuf, (*stack)->origin);
	/* Build up to the directory 'path' is in */
	while (pathbuf.len < dirlen) {
		size_t len = pathbuf.len;
		struct attr_stack *next;
		char *origin;

		/* Skip path-separator */
		if (len < dirlen && is_dir_sep(path[len]))
			len++;
		/* Find the end of the next component */
		while (len < dirlen && !is_dir_sep(path[len]))
			len++;

		if (pathbuf.len > 0)
			strbuf_addch(&pathbuf, '/');
		strbuf_add(&pathbuf, path + pathbuf.len, (len - pathbuf.len));
		strbuf_addf(&pathbuf, "/%s", GITATTRIBUTES_FILE);

		next = read_attr(istate, pathbuf.buf, 0);

		/* reset the pathbuf to not include "/.gitattributes" */
		strbuf_setlen(&pathbuf, len);

		origin = xstrdup(pathbuf.buf);
		push_stack(stack, next, origin, len);
	}

	/*
	 * Finally push the "info" one at the top of the stack.
	 */
	push_stack(stack, info, NULL, 0);

	strbuf_release(&pathbuf);
}