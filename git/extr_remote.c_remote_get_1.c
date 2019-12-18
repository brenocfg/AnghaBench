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
struct remote {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_url_alias (struct remote*,char const*) ; 
 struct branch* current_branch ; 
 scalar_t__ have_git_dir () ; 
 struct remote* make_remote (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_branches_file (struct remote*) ; 
 int /*<<< orphan*/  read_config () ; 
 int /*<<< orphan*/  read_remotes_file (struct remote*) ; 
 int /*<<< orphan*/  valid_remote (struct remote*) ; 
 scalar_t__ valid_remote_nick (char const*) ; 

__attribute__((used)) static struct remote *remote_get_1(const char *name,
				   const char *(*get_default)(struct branch *, int *))
{
	struct remote *ret;
	int name_given = 0;

	read_config();

	if (name)
		name_given = 1;
	else
		name = get_default(current_branch, &name_given);

	ret = make_remote(name, 0);
	if (valid_remote_nick(name) && have_git_dir()) {
		if (!valid_remote(ret))
			read_remotes_file(ret);
		if (!valid_remote(ret))
			read_branches_file(ret);
	}
	if (name_given && !valid_remote(ret))
		add_url_alias(ret, name);
	if (!valid_remote(ret))
		return NULL;
	return ret;
}