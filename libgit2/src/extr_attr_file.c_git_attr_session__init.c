#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  attr_session_key; } ;
typedef  TYPE_1__ git_repository ;
struct TYPE_8__ {int /*<<< orphan*/  key; } ;
typedef  TYPE_2__ git_attr_session ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  git_atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

int git_attr_session__init(git_attr_session *session, git_repository *repo)
{
	assert(repo);

	memset(session, 0, sizeof(*session));
	session->key = git_atomic_inc(&repo->attr_session_key);

	return 0;
}