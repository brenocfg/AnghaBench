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
struct shortlog {scalar_t__ email; int /*<<< orphan*/  mailmap; } ;
struct ident_split {char* name_begin; char* mail_begin; char* name_end; char* mail_end; } ;

/* Variables and functions */
 int /*<<< orphan*/  map_user (int /*<<< orphan*/ *,char const**,size_t*,char const**,size_t*) ; 
 scalar_t__ split_ident_line (struct ident_split*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char const*,size_t) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int,char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int parse_stdin_author(struct shortlog *log,
			       struct strbuf *out, const char *in)
{
	const char *mailbuf, *namebuf;
	size_t namelen, maillen;
	struct ident_split ident;

	if (split_ident_line(&ident, in, strlen(in)))
		return -1;

	namebuf = ident.name_begin;
	mailbuf = ident.mail_begin;
	namelen = ident.name_end - ident.name_begin;
	maillen = ident.mail_end - ident.mail_begin;

	map_user(&log->mailmap, &mailbuf, &maillen, &namebuf, &namelen);
	strbuf_add(out, namebuf, namelen);
	if (log->email)
		strbuf_addf(out, " <%.*s>", (int)maillen, mailbuf);

	return 0;
}