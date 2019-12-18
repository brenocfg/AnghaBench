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
struct nlmsghdr {scalar_t__ nlmsg_pid; int nlmsg_seq; scalar_t__ nlmsg_type; scalar_t__ nlmsg_len; } ;
struct nlmsgerr {int error; } ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int EIO ; 
 int MSG_TRUNC ; 
 scalar_t__ NLMSG_DATA (struct nlmsghdr*) ; 
 scalar_t__ NLMSG_DONE ; 
 scalar_t__ NLMSG_ERROR ; 
 scalar_t__ NLMSG_LENGTH (int) ; 
 scalar_t__ NLMSG_NEXT (struct nlmsghdr*,int) ; 
 scalar_t__ NLMSG_OK (struct nlmsghdr*,int) ; 
 int /*<<< orphan*/  __set_errno (int) ; 
 int errno ; 
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ getpid () ; 
 int nl_recvmsg (int,int,int,void*,size_t,int*) ; 
 void* realloc (void*,size_t) ; 

__attribute__((used)) static int
nl_getmsg(int sd, int request, int seq,
	  struct nlmsghdr **nlhp,
	  int *done)
{
  struct nlmsghdr *nh;
  size_t bufsize = 65536, lastbufsize = 0;
  void *buff = NULL;
  int result = 0, read_size;
  int msg_flags;
  pid_t pid = getpid();
  for (;;){
    void *newbuff = realloc(buff, bufsize);
    if (newbuff == NULL || bufsize < lastbufsize) {
      result = -1;
      break;
    }
    buff = newbuff;
    result = read_size = nl_recvmsg(sd, request, seq, buff, bufsize, &msg_flags);
    if (read_size < 0 || (msg_flags & MSG_TRUNC)){
      lastbufsize = bufsize;
      bufsize *= 2;
      continue;
    }
    if (read_size == 0) break;
    nh = (struct nlmsghdr *)buff;
    for (nh = (struct nlmsghdr *)buff;
	 NLMSG_OK(nh, read_size);
	 nh = (struct nlmsghdr *)NLMSG_NEXT(nh, read_size)){
      if (nh->nlmsg_pid != pid ||
	  nh->nlmsg_seq != seq)
	continue;
      if (nh->nlmsg_type == NLMSG_DONE){
	(*done)++;
	break; /* ok */
      }
      if (nh->nlmsg_type == NLMSG_ERROR){
	struct nlmsgerr *nlerr = (struct nlmsgerr *)NLMSG_DATA(nh);
	result = -1;
	if (nh->nlmsg_len < NLMSG_LENGTH(sizeof(struct nlmsgerr)))
	  __set_errno(EIO);
	else
	  __set_errno(-nlerr->error);
	break;
      }
    }
    break;
  }
  if (result < 0)
    if (buff){
      int saved_errno = errno;
      free(buff);
      __set_errno(saved_errno);
    }
  *nlhp = (struct nlmsghdr *)buff;
  return result;
}