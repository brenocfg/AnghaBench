#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct timeval {scalar_t__ tv_usec; int /*<<< orphan*/  tv_sec; } ;
typedef  scalar_t__ krb5_socket_t ;
struct TYPE_5__ {size_t length; void* data; } ;
typedef  TYPE_1__ krb5_data ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  FD_SET (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ FD_SETSIZE ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FIONREAD ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  krb5_data_free (TYPE_1__*) ; 
 int /*<<< orphan*/  krb5_data_zero (TYPE_1__*) ; 
 int min (size_t,size_t) ; 
 void* realloc (void*,size_t) ; 
 int recv (scalar_t__,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ rk_SOCK_IOCTL (scalar_t__,int /*<<< orphan*/ ,int*) ; 
 int select (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 

__attribute__((used)) static int
recv_loop (krb5_socket_t fd,
	   time_t tmout,
	   int udp,
	   size_t limit,
	   krb5_data *rep)
{
     fd_set fdset;
     struct timeval timeout;
     int ret;
     int nbytes;

#ifndef NO_LIMIT_FD_SETSIZE
     if (fd >= FD_SETSIZE) {
	 return -1;
     }
#endif

     krb5_data_zero(rep);
     do {
	 FD_ZERO(&fdset);
	 FD_SET(fd, &fdset);
	 timeout.tv_sec  = tmout;
	 timeout.tv_usec = 0;
	 ret = select (fd + 1, &fdset, NULL, NULL, &timeout);
	 if (ret < 0) {
	     if (errno == EINTR)
		 continue;
	     return -1;
	 } else if (ret == 0) {
	     return 0;
	 } else {
	     void *tmp;

	     if (rk_SOCK_IOCTL (fd, FIONREAD, &nbytes) < 0) {
		 krb5_data_free (rep);
		 return -1;
	     }
	     if(nbytes <= 0)
		 return 0;

	     if (limit)
		 nbytes = min((size_t)nbytes, limit - rep->length);

	     tmp = realloc (rep->data, rep->length + nbytes);
	     if (tmp == NULL) {
		 krb5_data_free (rep);
		 return -1;
	     }
	     rep->data = tmp;
	     ret = recv (fd, (char*)tmp + rep->length, nbytes, 0);
	     if (ret < 0) {
		 krb5_data_free (rep);
		 return -1;
	     }
	     rep->length += ret;
	 }
     } while(!udp && (limit == 0 || rep->length < limit));
     return 0;
}