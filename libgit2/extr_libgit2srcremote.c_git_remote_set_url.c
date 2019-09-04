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
typedef  int /*<<< orphan*/  git_repository ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_URL_FMT ; 
 int set_url (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,char const*) ; 

int git_remote_set_url(git_repository *repo, const char *remote, const char *url)
{
	return set_url(repo, remote, CONFIG_URL_FMT, url);
}