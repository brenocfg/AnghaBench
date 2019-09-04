#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ign_path; int /*<<< orphan*/  depth; } ;
typedef  TYPE_1__ git_ignores ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_IGNORE_FILE ; 
 int push_ignore_file (TYPE_1__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int push_one_ignore(void *payload, const char *path)
{
	git_ignores *ign = payload;
	ign->depth++;
	return push_ignore_file(ign, &ign->ign_path, path, GIT_IGNORE_FILE);
}