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
typedef  void git_buf ;

/* Variables and functions */
 int GIT_PASSTHROUGH ; 
 int /*<<< orphan*/  GIT_UNUSED (void*) ; 

__attribute__((used)) static int urlresolve_passthrough_callback(git_buf *url_resolved, const char *url, int direction, void *payload)
{
	GIT_UNUSED(url_resolved);
	GIT_UNUSED(url);
	GIT_UNUSED(direction);
	GIT_UNUSED(payload);
	return GIT_PASSTHROUGH;
}