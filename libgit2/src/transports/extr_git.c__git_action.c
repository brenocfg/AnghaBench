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
typedef  int /*<<< orphan*/  git_subtransport ;
typedef  int /*<<< orphan*/  git_smart_subtransport_stream ;
typedef  int /*<<< orphan*/  git_smart_subtransport ;
typedef  int git_smart_service_t ;

/* Variables and functions */
#define  GIT_SERVICE_RECEIVEPACK 131 
#define  GIT_SERVICE_RECEIVEPACK_LS 130 
#define  GIT_SERVICE_UPLOADPACK 129 
#define  GIT_SERVICE_UPLOADPACK_LS 128 
 int _git_receivepack (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ **) ; 
 int _git_receivepack_ls (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ **) ; 
 int _git_uploadpack (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ **) ; 
 int _git_uploadpack_ls (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int _git_action(
	git_smart_subtransport_stream **stream,
	git_smart_subtransport *subtransport,
	const char *url,
	git_smart_service_t action)
{
	git_subtransport *t = (git_subtransport *) subtransport;

	switch (action) {
		case GIT_SERVICE_UPLOADPACK_LS:
			return _git_uploadpack_ls(t, url, stream);

		case GIT_SERVICE_UPLOADPACK:
			return _git_uploadpack(t, url, stream);

		case GIT_SERVICE_RECEIVEPACK_LS:
			return _git_receivepack_ls(t, url, stream);

		case GIT_SERVICE_RECEIVEPACK:
			return _git_receivepack(t, url, stream);
	}

	*stream = NULL;
	return -1;
}