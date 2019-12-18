#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  free; int /*<<< orphan*/  credtype; } ;
struct TYPE_6__ {int /*<<< orphan*/  username; TYPE_1__ parent; } ;
typedef  TYPE_2__ git_cred_username ;
typedef  int /*<<< orphan*/  git_cred ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_CREDTYPE_USERNAME ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_2__*) ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC_ADD (size_t*,size_t,int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ **) ; 
 TYPE_2__* git__malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,size_t) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  username_free ; 

int git_cred_username_new(git_cred **cred, const char *username)
{
	git_cred_username *c;
	size_t len, allocsize;

	assert(cred);

	len = strlen(username);

	GIT_ERROR_CHECK_ALLOC_ADD(&allocsize, sizeof(git_cred_username), len);
	GIT_ERROR_CHECK_ALLOC_ADD(&allocsize, allocsize, 1);
	c = git__malloc(allocsize);
	GIT_ERROR_CHECK_ALLOC(c);

	c->parent.credtype = GIT_CREDTYPE_USERNAME;
	c->parent.free = username_free;
	memcpy(c->username, username, len + 1);

	*cred = (git_cred *) c;
	return 0;
}