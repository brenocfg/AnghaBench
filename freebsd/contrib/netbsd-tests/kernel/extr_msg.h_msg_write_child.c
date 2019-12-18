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
struct msg_fds {int /*<<< orphan*/ * cfd; int /*<<< orphan*/ * pfd; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOSEFD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 scalar_t__ read (int /*<<< orphan*/ ,void*,size_t) ; 
 scalar_t__ write (int /*<<< orphan*/ ,void*,size_t) ; 

__attribute__((used)) static int
msg_write_child(const char *info, struct msg_fds *fds, void *msg, size_t len)
{
	ssize_t rv;
	CLOSEFD(fds->cfd[1]);
	CLOSEFD(fds->pfd[0]);

	printf("Send %s\n", info);
	rv = write(fds->pfd[1], msg, len);
	if (rv != (ssize_t)len)
		return 1;
//	printf("Wait %s\n", info);
	rv = read(fds->cfd[0], msg, len);
	if (rv != (ssize_t)len)
		return 1;
	return 0;
}