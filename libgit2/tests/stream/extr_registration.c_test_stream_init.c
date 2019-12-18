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
typedef  int /*<<< orphan*/  git_stream ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_UNUSED (char const*) ; 
 int ctor_called ; 
 int /*<<< orphan*/  test_stream ; 

__attribute__((used)) static int test_stream_init(git_stream **out, const char *host, const char *port)
{
	GIT_UNUSED(host);
	GIT_UNUSED(port);

	ctor_called = 1;
	*out = &test_stream;

	return 0;
}