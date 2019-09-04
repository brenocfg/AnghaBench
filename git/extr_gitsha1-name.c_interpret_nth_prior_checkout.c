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
struct strbuf {int dummy; } ;
struct grab_nth_branch_switch_cbdata {long remaining; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 scalar_t__ for_each_reflog_ent_reverse (char*,int /*<<< orphan*/ ,struct grab_nth_branch_switch_cbdata*) ; 
 int /*<<< orphan*/  grab_nth_branch_switch ; 
 char* memchr (char const*,char,int) ; 
 int /*<<< orphan*/  strbuf_addbuf (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strbuf_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 long strtol (char const*,char**,int) ; 

__attribute__((used)) static int interpret_nth_prior_checkout(const char *name, int namelen,
					struct strbuf *buf)
{
	long nth;
	int retval;
	struct grab_nth_branch_switch_cbdata cb;
	const char *brace;
	char *num_end;

	if (namelen < 4)
		return -1;
	if (name[0] != '@' || name[1] != '{' || name[2] != '-')
		return -1;
	brace = memchr(name, '}', namelen);
	if (!brace)
		return -1;
	nth = strtol(name + 3, &num_end, 10);
	if (num_end != brace)
		return -1;
	if (nth <= 0)
		return -1;
	cb.remaining = nth;
	strbuf_init(&cb.buf, 20);

	retval = 0;
	if (0 < for_each_reflog_ent_reverse("HEAD", grab_nth_branch_switch, &cb)) {
		strbuf_reset(buf);
		strbuf_addbuf(buf, &cb.buf);
		retval = brace - name + 1;
	}

	strbuf_release(&cb.buf);
	return retval;
}