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
typedef  int /*<<< orphan*/  git_net_url ;
typedef  int /*<<< orphan*/  git_http_auth_context ;

/* Variables and functions */
 int GIT_PASSTHROUGH ; 
 int /*<<< orphan*/  GIT_UNUSED (int /*<<< orphan*/  const*) ; 

int git_http_auth_dummy(
	git_http_auth_context **out, const git_net_url *url)
{
	GIT_UNUSED(url);

	*out = NULL;
	return GIT_PASSTHROUGH;
}