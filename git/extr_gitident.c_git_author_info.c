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

/* Variables and functions */
 int /*<<< orphan*/  IDENT_MAIL_GIVEN ; 
 int /*<<< orphan*/  IDENT_NAME_GIVEN ; 
 int /*<<< orphan*/  WANT_AUTHOR_IDENT ; 
 int /*<<< orphan*/  author_ident_explicitly_given ; 
 char const* fmt_ident (scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ getenv (char*) ; 

const char *git_author_info(int flag)
{
	if (getenv("GIT_AUTHOR_NAME"))
		author_ident_explicitly_given |= IDENT_NAME_GIVEN;
	if (getenv("GIT_AUTHOR_EMAIL"))
		author_ident_explicitly_given |= IDENT_MAIL_GIVEN;
	return fmt_ident(getenv("GIT_AUTHOR_NAME"),
			 getenv("GIT_AUTHOR_EMAIL"),
			 WANT_AUTHOR_IDENT,
			 getenv("GIT_AUTHOR_DATE"),
			 flag);
}