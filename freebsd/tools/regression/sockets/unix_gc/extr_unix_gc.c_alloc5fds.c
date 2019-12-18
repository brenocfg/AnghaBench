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

/* Variables and functions */
 int /*<<< orphan*/  PF_UNIX ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ ) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ socketpair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  test ; 

__attribute__((used)) static void
alloc5fds(int *s, int *sva, int *svb)
{

	if ((*s = socket(PF_UNIX, SOCK_STREAM, 0)) < 0)
		err(-1, "%s: socket", test);
	if (socketpair(PF_UNIX, SOCK_STREAM, 0, sva) < 0)
		err(-1, "%s: socketpair", test);
	if (socketpair(PF_UNIX, SOCK_STREAM, 0, svb) < 0)
		err(-1, "%s: socketpair", test);
}