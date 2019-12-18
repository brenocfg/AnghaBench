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
typedef  int /*<<< orphan*/  git_mailmap ;

/* Variables and functions */
 int mailmap_add_entry_unterminated (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int git_mailmap_add_entry(
	git_mailmap *mm, const char *real_name, const char *real_email,
	const char *replace_name, const char *replace_email)
{
	return mailmap_add_entry_unterminated(
		mm,
		real_name, real_name ? strlen(real_name) : 0,
		real_email, real_email ? strlen(real_email) : 0,
		replace_name, replace_name ? strlen(replace_name) : 0,
		replace_email, strlen(replace_email));
}