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
typedef  int /*<<< orphan*/  git_cred ;

/* Variables and functions */
 unsigned int GIT_CREDTYPE_DEFAULT ; 
 int /*<<< orphan*/  GIT_UNUSED (void*) ; 
 int git_cred_default_new (int /*<<< orphan*/ **) ; 

int cred_default(
	git_cred **cred,
	const char *url,
	const char *user_from_url,
	unsigned int allowed_types,
	void *payload)
{
	GIT_UNUSED(url);
	GIT_UNUSED(user_from_url);
	GIT_UNUSED(payload);

	if (!(allowed_types & GIT_CREDTYPE_DEFAULT))
		return 0;

	return git_cred_default_new(cred);
}