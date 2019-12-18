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
struct stat {scalar_t__ st_dev; scalar_t__ st_ino; int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  INVALID_SOCKET ; 
 int /*<<< orphan*/  L_Mutex ; 
 scalar_t__ S_ISFIFO (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISSOCK (int /*<<< orphan*/ ) ; 
 scalar_t__ ValidSocket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  closesocket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ fstat (int /*<<< orphan*/ ,struct stat*) ; 
 scalar_t__ geteuid () ; 
 int /*<<< orphan*/  listenfd ; 
 int /*<<< orphan*/  smutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sockpath ; 
 scalar_t__ stat (int /*<<< orphan*/ *,struct stat*) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ *) ; 

void
mi_closener()
{
	(void) smutex_lock(&L_Mutex);
	if (ValidSocket(listenfd))
	{
#if NETUNIX
		bool removable;
		struct stat sockinfo;
		struct stat fileinfo;

		removable = sockpath != NULL &&
			    geteuid() != 0 &&
			    fstat(listenfd, &sockinfo) == 0 &&
			    (S_ISFIFO(sockinfo.st_mode)
# ifdef S_ISSOCK
			     || S_ISSOCK(sockinfo.st_mode)
# endif /* S_ISSOCK */
			    );
#endif /* NETUNIX */

		(void) closesocket(listenfd);
		listenfd = INVALID_SOCKET;

#if NETUNIX
		/* XXX sleep() some time before doing this? */
		if (sockpath != NULL)
		{
			if (removable &&
			    stat(sockpath, &fileinfo) == 0 &&
			    ((fileinfo.st_dev == sockinfo.st_dev &&
			      fileinfo.st_ino == sockinfo.st_ino)
# ifdef S_ISSOCK
			     || S_ISSOCK(fileinfo.st_mode)
# endif /* S_ISSOCK */
			    )
			    &&
			    (S_ISFIFO(fileinfo.st_mode)
# ifdef S_ISSOCK
			     || S_ISSOCK(fileinfo.st_mode)
# endif /* S_ISSOCK */
			     ))
				(void) unlink(sockpath);
			free(sockpath);
			sockpath = NULL;
		}
#endif /* NETUNIX */
	}
	(void) smutex_unlock(&L_Mutex);
}