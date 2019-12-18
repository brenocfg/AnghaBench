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
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int DTF_HIDEW ; 
 int DTF_NODUP ; 
 int /*<<< orphan*/  FD_CLOEXEC ; 
 int /*<<< orphan*/  F_SETFD ; 
 int /*<<< orphan*/ * __opendir_common (int,int,int) ; 
 int _fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

DIR *
fdopendir(int fd)
{

	if (_fcntl(fd, F_SETFD, FD_CLOEXEC) == -1)
		return (NULL);
	return (__opendir_common(fd, DTF_HIDEW|DTF_NODUP, true));
}