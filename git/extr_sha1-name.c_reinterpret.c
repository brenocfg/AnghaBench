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
struct repository {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int repo_interpret_branch_name (struct repository*,int /*<<< orphan*/ ,int,struct strbuf*,unsigned int) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char const*,int) ; 
 int /*<<< orphan*/  strbuf_addbuf (struct strbuf*,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,int) ; 

__attribute__((used)) static int reinterpret(struct repository *r,
		       const char *name, int namelen, int len,
		       struct strbuf *buf, unsigned allowed)
{
	/* we have extra data, which might need further processing */
	struct strbuf tmp = STRBUF_INIT;
	int used = buf->len;
	int ret;

	strbuf_add(buf, name + len, namelen - len);
	ret = repo_interpret_branch_name(r, buf->buf, buf->len, &tmp, allowed);
	/* that data was not interpreted, remove our cruft */
	if (ret < 0) {
		strbuf_setlen(buf, used);
		return len;
	}
	strbuf_reset(buf);
	strbuf_addbuf(buf, &tmp);
	strbuf_release(&tmp);
	/* tweak for size of {-N} versus expanded ref name */
	return ret - used + len;
}