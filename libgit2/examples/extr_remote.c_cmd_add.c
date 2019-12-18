#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct opts {int argc; char** argv; } ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_remote ;
struct TYPE_2__ {int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_lg2 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_create (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  usage (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cmd_add(git_repository *repo, struct opts *o)
{
	char *name, *url;
	git_remote *remote = {0};

	if (o->argc != 2)
		usage("you need to specify a name and URL", NULL);

	name = o->argv[0];
	url = o->argv[1];

	check_lg2(git_remote_create(&remote, repo, name, url),
			"could not create remote", NULL);

	return 0;
}