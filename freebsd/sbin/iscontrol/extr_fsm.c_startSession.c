#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int trans_t ;
struct TYPE_4__ {int flags; int fd; int soc; scalar_t__ isid; } ;
typedef  TYPE_1__ isess_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSISETSES ; 
 int /*<<< orphan*/  ISCSISETSOC ; 
 int /*<<< orphan*/  O_RDWR ; 
 int SESS_CONNECTED ; 
 int T2 ; 
 int T4 ; 
 int /*<<< orphan*/  asprintf (char**,char*,char*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int*) ; 
 char* iscsidev ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ setOptions (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ sysctlbyname (char*,void*,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static trans_t
startSession(isess_t *sess)
{
     
     int	n, fd, nfd;
     char	*dev;

     debug_called(3);

     if((sess->flags & SESS_CONNECTED) == 0) {
	  return T2;
     }
     if(sess->fd == -1) {
	  fd = open(iscsidev, O_RDWR);
	  if(fd < 0) {
	       perror(iscsidev);
	       return 0;
	  }
	  {
	       // XXX: this has to go
	       size_t	n;
	       n = sizeof(sess->isid);
	       if(sysctlbyname("net.iscsi_initiator.isid", (void *)sess->isid, (size_t *)&n, 0, 0) != 0)
		    perror("sysctlbyname");
	  }
	  if(ioctl(fd, ISCSISETSES, &n)) {
	       perror("ISCSISETSES");
	       return 0;
	  }
	  asprintf(&dev, "%s%d", iscsidev, n);
	  nfd = open(dev, O_RDWR);
	  if(nfd < 0) {
	       perror(dev);
	       free(dev);
	       return 0;
	  }
	  free(dev);
	  close(fd);
	  sess->fd = nfd;

	  if(setOptions(sess, 0) != 0)
	       return -1;
     }

     if(ioctl(sess->fd, ISCSISETSOC, &sess->soc)) {
	  perror("ISCSISETSOC");
	  return 0;
     }

     return T4;
}