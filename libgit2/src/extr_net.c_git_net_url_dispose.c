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
struct TYPE_3__ {int /*<<< orphan*/ * password; int /*<<< orphan*/ * username; int /*<<< orphan*/ * path; int /*<<< orphan*/ * port; int /*<<< orphan*/ * host; int /*<<< orphan*/ * scheme; } ;
typedef  TYPE_1__ git_net_url ;

/* Variables and functions */
 int /*<<< orphan*/  git__free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git__memzero (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ *) ; 

void git_net_url_dispose(git_net_url *url)
{
	if (url->username)
		git__memzero(url->username, strlen(url->username));

	if (url->password)
		git__memzero(url->password, strlen(url->password));

	git__free(url->scheme); url->scheme = NULL;
	git__free(url->host); url->host = NULL;
	git__free(url->port); url->port = NULL;
	git__free(url->path); url->path = NULL;
	git__free(url->username); url->username = NULL;
	git__free(url->password); url->password = NULL;
}