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

/* Variables and functions */
 int /*<<< orphan*/  strbuf_addbuf (struct strbuf*,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 scalar_t__ strchr (int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static void get_sane_name(struct strbuf *out, struct strbuf *name, struct strbuf *email)
{
	struct strbuf *src = name;
	if (name->len < 3 || 60 < name->len || strchr(name->buf, '@') ||
		strchr(name->buf, '<') || strchr(name->buf, '>'))
		src = email;
	else if (name == out)
		return;
	strbuf_reset(out);
	strbuf_addbuf(out, src);
}