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
struct TYPE_3__ {int /*<<< orphan*/  wVersion; } ;
typedef  TYPE_1__ WSADATA ;

/* Variables and functions */
 int HIBYTE (int /*<<< orphan*/ ) ; 
 int LOBYTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEWORD (int,int) ; 
 int /*<<< orphan*/  WSAStartup (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 

void test_core_posix__initialize(void)
{
#ifdef GIT_WIN32
	/* on win32, the WSA context needs to be initialized
	 * before any socket calls can be performed */
	WSADATA wsd;

	cl_git_pass(WSAStartup(MAKEWORD(2,2), &wsd));
	cl_assert(LOBYTE(wsd.wVersion) == 2 && HIBYTE(wsd.wVersion) == 2);
#endif
}