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
struct TYPE_3__ {int (* resolve_url ) (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  payload; } ;
typedef  TYPE_1__ git_remote_callbacks ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int GIT_PASSTHROUGH ; 
 int /*<<< orphan*/  git_buf_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_sanitize (int /*<<< orphan*/ *) ; 
 int git_buf_sets (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_error_set_after_callback_function (int,char*) ; 
 int stub1 (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int resolve_url(git_buf *resolved_url, const char *url, int direction, const git_remote_callbacks *callbacks)
{
	int status;

	if (callbacks && callbacks->resolve_url) {
		git_buf_clear(resolved_url);
		status = callbacks->resolve_url(resolved_url, url, direction, callbacks->payload);
		if (status != GIT_PASSTHROUGH) {
			git_error_set_after_callback_function(status, "git_resolve_url_cb");
			git_buf_sanitize(resolved_url);
			return status;
		}
	}

	return git_buf_sets(resolved_url, url);
}