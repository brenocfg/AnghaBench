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
typedef  int /*<<< orphan*/  git_diff_driver ;
struct TYPE_3__ {char* ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_UNUSED (int /*<<< orphan*/ *) ; 
 scalar_t__ git__isalpha (char) ; 

__attribute__((used)) static int diff_context_line__simple(
	git_diff_driver *driver, git_buf *line)
{
	char firstch = line->ptr[0];
	GIT_UNUSED(driver);
	return (git__isalpha(firstch) || firstch == '_' || firstch == '$');
}