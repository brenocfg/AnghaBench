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
struct unix_sockaddr_context {int dummy; } ;
struct sockaddr_un {int dummy; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  sa ;

/* Variables and functions */
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 scalar_t__ listen (int,int) ; 
 int /*<<< orphan*/  unix_sockaddr_cleanup (struct unix_sockaddr_context*) ; 
 scalar_t__ unix_sockaddr_init (struct sockaddr_un*,char const*,struct unix_sockaddr_context*) ; 
 int unix_stream_socket () ; 
 int /*<<< orphan*/  unlink (char const*) ; 

int unix_stream_listen(const char *path)
{
	int fd, saved_errno;
	struct sockaddr_un sa;
	struct unix_sockaddr_context ctx;

	unlink(path);

	if (unix_sockaddr_init(&sa, path, &ctx) < 0)
		return -1;
	fd = unix_stream_socket();

	if (bind(fd, (struct sockaddr *)&sa, sizeof(sa)) < 0)
		goto fail;

	if (listen(fd, 5) < 0)
		goto fail;

	unix_sockaddr_cleanup(&ctx);
	return fd;

fail:
	saved_errno = errno;
	unix_sockaddr_cleanup(&ctx);
	close(fd);
	errno = saved_errno;
	return -1;
}