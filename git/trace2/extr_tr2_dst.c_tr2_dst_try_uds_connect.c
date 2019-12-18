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
struct sockaddr_un {int /*<<< orphan*/  sun_path; int /*<<< orphan*/  sun_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  sa ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int /*<<< orphan*/  close (int) ; 
 int connect (int,struct sockaddr*,int) ; 
 int errno ; 
 int socket (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static int tr2_dst_try_uds_connect(const char *path, int sock_type, int *out_fd)
{
	int fd;
	struct sockaddr_un sa;

	fd = socket(AF_UNIX, sock_type, 0);
	if (fd == -1)
		return errno;

	sa.sun_family = AF_UNIX;
	strlcpy(sa.sun_path, path, sizeof(sa.sun_path));

	if (connect(fd, (struct sockaddr *)&sa, sizeof(sa)) == -1) {
		int e = errno;
		close(fd);
		return e;
	}

	*out_fd = fd;
	return 0;
}