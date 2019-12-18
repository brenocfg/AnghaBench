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
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int EINTR ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int errno ; 
 scalar_t__ waitpid (scalar_t__,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
safe_waitpid(pid_t pid)
{
	int save_errno;
	int status;

	save_errno = errno;
	errno = 0;
	while (waitpid(pid, &status, 0) != pid) {
		if (errno == EINTR)
			continue;
		err(1, "waitpid");
	}
	errno = save_errno;

	return (status);
}