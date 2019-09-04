#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  tmp; int /*<<< orphan*/  sysdir; } ;
typedef  TYPE_1__ git_attr_session ;

/* Variables and functions */
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void git_attr_session__free(git_attr_session *session)
{
	if (!session)
		return;

	git_buf_dispose(&session->sysdir);
	git_buf_dispose(&session->tmp);

	memset(session, 0, sizeof(git_attr_session));
}