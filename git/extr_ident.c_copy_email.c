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
struct passwd {int /*<<< orphan*/  pw_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_domainname (struct strbuf*,int*) ; 
 int /*<<< orphan*/  add_mailname_host (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void copy_email(const struct passwd *pw, struct strbuf *email,
		       int *is_bogus)
{
	/*
	 * Make up a fake email address
	 * (name + '@' + hostname [+ '.' + domainname])
	 */
	strbuf_addstr(email, pw->pw_name);
	strbuf_addch(email, '@');

	if (!add_mailname_host(email))
		return;	/* read from "/etc/mailname" (Debian) */
	add_domainname(email, is_bogus);
}