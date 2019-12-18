#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct strbuf {int len; char* buf; } ;
struct TYPE_4__ {scalar_t__ len; } ;
struct mailinfo {TYPE_1__ email; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  cleanup_space (struct strbuf*) ; 
 int /*<<< orphan*/  get_sane_name (int /*<<< orphan*/ *,struct strbuf*,TYPE_1__*) ; 
 scalar_t__ isspace (char) ; 
 int /*<<< orphan*/  parse_bogus_from (struct mailinfo*,struct strbuf const*) ; 
 int /*<<< orphan*/  strbuf_add (TYPE_1__*,char*,size_t) ; 
 int /*<<< orphan*/  strbuf_addbuf (struct strbuf*,struct strbuf const*) ; 
 int /*<<< orphan*/  strbuf_init (struct strbuf*,int) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_remove (struct strbuf*,int,int) ; 
 int /*<<< orphan*/  strbuf_reset (TYPE_1__*) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,int) ; 
 int /*<<< orphan*/  strbuf_trim (struct strbuf*) ; 
 char* strchr (char*,char) ; 
 size_t strcspn (char*,char*) ; 
 int /*<<< orphan*/  unquote_quoted_pair (struct strbuf*) ; 

__attribute__((used)) static void handle_from(struct mailinfo *mi, const struct strbuf *from)
{
	char *at;
	size_t el;
	struct strbuf f;

	strbuf_init(&f, from->len);
	strbuf_addbuf(&f, from);

	unquote_quoted_pair(&f);

	at = strchr(f.buf, '@');
	if (!at) {
		parse_bogus_from(mi, from);
		goto out;
	}

	/*
	 * If we already have one email, don't take any confusing lines
	 */
	if (mi->email.len && strchr(at + 1, '@'))
		goto out;

	/* Pick up the string around '@', possibly delimited with <>
	 * pair; that is the email part.
	 */
	while (at > f.buf) {
		char c = at[-1];
		if (isspace(c))
			break;
		if (c == '<') {
			at[-1] = ' ';
			break;
		}
		at--;
	}
	el = strcspn(at, " \n\t\r\v\f>");
	strbuf_reset(&mi->email);
	strbuf_add(&mi->email, at, el);
	strbuf_remove(&f, at - f.buf, el + (at[el] ? 1 : 0));

	/* The remainder is name.  It could be
	 *
	 * - "John Doe <john.doe@xz>"			(a), or
	 * - "john.doe@xz (John Doe)"			(b), or
	 * - "John (zzz) Doe <john.doe@xz> (Comment)"	(c)
	 *
	 * but we have removed the email part, so
	 *
	 * - remove extra spaces which could stay after email (case 'c'), and
	 * - trim from both ends, possibly removing the () pair at the end
	 *   (cases 'a' and 'b').
	 */
	cleanup_space(&f);
	strbuf_trim(&f);
	if (f.buf[0] == '(' && f.len && f.buf[f.len - 1] == ')') {
		strbuf_remove(&f, 0, 1);
		strbuf_setlen(&f, f.len - 1);
	}

	get_sane_name(&mi->name, &f, &mi->email);
out:
	strbuf_release(&f);
}