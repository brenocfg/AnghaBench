#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char const* buf; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int IDENT_MAIL_GIVEN ; 
 int author_ident_explicitly_given ; 
 int committer_ident_explicitly_given ; 
 int /*<<< orphan*/  copy_email (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  default_email_is_bogus ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 TYPE_1__ git_default_email ; 
 int ident_config_given ; 
 char* query_user_email () ; 
 int /*<<< orphan*/  strbuf_addstr (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  strbuf_trim (TYPE_1__*) ; 
 int /*<<< orphan*/  xgetpwuid_self (int /*<<< orphan*/ *) ; 

const char *ident_default_email(void)
{
	if (!(ident_config_given & IDENT_MAIL_GIVEN) && !git_default_email.len) {
		const char *email = getenv("EMAIL");

		if (email && email[0]) {
			strbuf_addstr(&git_default_email, email);
			committer_ident_explicitly_given |= IDENT_MAIL_GIVEN;
			author_ident_explicitly_given |= IDENT_MAIL_GIVEN;
		} else if ((email = query_user_email()) && email[0]) {
			strbuf_addstr(&git_default_email, email);
			free((char *)email);
		} else
			copy_email(xgetpwuid_self(&default_email_is_bogus),
				   &git_default_email, &default_email_is_bogus);
		strbuf_trim(&git_default_email);
	}
	return git_default_email.buf;
}