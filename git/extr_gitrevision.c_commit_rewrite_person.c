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
struct string_list {int dummy; } ;
struct strbuf {int buf; int /*<<< orphan*/  len; } ;
struct ident_split {char* mail_begin; char* mail_end; char* name_begin; char* name_end; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 scalar_t__ map_user (struct string_list*,char const**,size_t*,char const**,size_t*) ; 
 scalar_t__ split_ident_line (struct ident_split*,char*,size_t) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int,char const*,int,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_splice (struct strbuf*,char*,int,int,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 char* strstr (int,char const*) ; 

__attribute__((used)) static int commit_rewrite_person(struct strbuf *buf, const char *what, struct string_list *mailmap)
{
	char *person, *endp;
	size_t len, namelen, maillen;
	const char *name;
	const char *mail;
	struct ident_split ident;

	person = strstr(buf->buf, what);
	if (!person)
		return 0;

	person += strlen(what);
	endp = strchr(person, '\n');
	if (!endp)
		return 0;

	len = endp - person;

	if (split_ident_line(&ident, person, len))
		return 0;

	mail = ident.mail_begin;
	maillen = ident.mail_end - ident.mail_begin;
	name = ident.name_begin;
	namelen = ident.name_end - ident.name_begin;

	if (map_user(mailmap, &mail, &maillen, &name, &namelen)) {
		struct strbuf namemail = STRBUF_INIT;

		strbuf_addf(&namemail, "%.*s <%.*s>",
			    (int)namelen, name, (int)maillen, mail);

		strbuf_splice(buf, ident.name_begin - buf->buf,
			      ident.mail_end - ident.name_begin + 1,
			      namemail.buf, namemail.len);

		strbuf_release(&namemail);

		return 1;
	}

	return 0;
}