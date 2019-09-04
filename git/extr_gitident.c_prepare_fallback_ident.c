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
 int /*<<< orphan*/  author_ident_explicitly_given ; 
 int /*<<< orphan*/  committer_ident_explicitly_given ; 
 int /*<<< orphan*/  set_env_if (char*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void prepare_fallback_ident(const char *name, const char *email)
{
	set_env_if("GIT_AUTHOR_NAME", name,
		   &author_ident_explicitly_given, IDENT_NAME_GIVEN);
	set_env_if("GIT_AUTHOR_EMAIL", email,
		   &author_ident_explicitly_given, IDENT_MAIL_GIVEN);
	set_env_if("GIT_COMMITTER_NAME", name,
		   &committer_ident_explicitly_given, IDENT_NAME_GIVEN);
	set_env_if("GIT_COMMITTER_EMAIL", email,
		   &committer_ident_explicitly_given, IDENT_MAIL_GIVEN);
}