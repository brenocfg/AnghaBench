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
struct ifnet {char* if_xname; char* if_name; int /*<<< orphan*/  if_unit; void* if_output; } ;

/* Variables and functions */
 int O_CREAT ; 
 int O_EXCL ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  close (int) ; 
 struct ifnet** ifneta ; 
 int open (char*,int,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,...) ; 
 scalar_t__ write_output ; 

void
init_ifp()
{
	struct ifnet *ifp, **ifpp;
	char fname[32];
	int fd;

#if (defined(NetBSD) && (NetBSD <= 1991011) && (NetBSD >= 199606)) || \
    defined(__FreeBSD__)
	for (ifpp = ifneta; ifpp && (ifp = *ifpp); ifpp++) {
		ifp->if_output = (void *)write_output;
		sprintf(fname, "/tmp/%s", ifp->if_xname);
		fd = open(fname, O_WRONLY|O_CREAT|O_EXCL|O_TRUNC, 0600);
		if (fd == -1)
			perror("open");
		else
			close(fd);
	}
#else

	for (ifpp = ifneta; ifpp && (ifp = *ifpp); ifpp++) {
		ifp->if_output = (void *)write_output;
		sprintf(fname, "/tmp/%s%d", ifp->if_name, ifp->if_unit);
		fd = open(fname, O_WRONLY|O_CREAT|O_EXCL|O_TRUNC, 0600);
		if (fd == -1)
			perror("open");
		else
			close(fd);
	}
#endif
}