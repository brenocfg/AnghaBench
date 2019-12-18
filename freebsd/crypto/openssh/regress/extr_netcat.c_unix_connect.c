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

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int /*<<< orphan*/  ENAMETOOLONG ; 
 int /*<<< orphan*/  FD_CLOEXEC ; 
 int /*<<< orphan*/  F_SETFD ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SUN_LEN (struct sockaddr_un*) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connect (int,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct sockaddr_un*,int /*<<< orphan*/ ,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ uflag ; 
 int unix_bind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unix_dg_tmp_socket ; 

int
unix_connect(char *path)
{
	struct sockaddr_un sun_sa;
	int s;

	if (uflag) {
		if ((s = unix_bind(unix_dg_tmp_socket)) < 0)
			return (-1);
	} else {
		if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
			return (-1);
	}
	(void)fcntl(s, F_SETFD, FD_CLOEXEC);

	memset(&sun_sa, 0, sizeof(struct sockaddr_un));
	sun_sa.sun_family = AF_UNIX;

	if (strlcpy(sun_sa.sun_path, path, sizeof(sun_sa.sun_path)) >=
	    sizeof(sun_sa.sun_path)) {
		close(s);
		errno = ENAMETOOLONG;
		return (-1);
	}
	if (connect(s, (struct sockaddr *)&sun_sa, SUN_LEN(&sun_sa)) < 0) {
		close(s);
		return (-1);
	}
	return (s);

}