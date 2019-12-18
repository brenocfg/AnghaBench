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
struct pollfd {int fd; int events; scalar_t__ revents; } ;
struct nlmsghdr {int dummy; } ;
struct nlmsg_list {int size; int seq; struct nlmsg_list* nlm_next; struct nlmsghdr* nlh; } ;

/* Variables and functions */
 int NLM_F_MATCH ; 
 int NLM_F_ROOT ; 
 int POLLIN ; 
 int POLLPRI ; 
 int /*<<< orphan*/  __set_errno (int) ; 
 int errno ; 
 int /*<<< orphan*/  free (struct nlmsghdr*) ; 
 scalar_t__ malloc (int) ; 
 int nl_getmsg (int,int,int,struct nlmsghdr**,int*) ; 
 int nl_sendreq (int,int,int,int*) ; 
 int poll (struct pollfd*,int,int) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nl_getlist(int sd, int seq,
	   int request,
	   struct nlmsg_list **nlm_list,
	   struct nlmsg_list **nlm_end)
{
  struct nlmsghdr *nlh = NULL;
  int status;
  int done = 0;
  int tries = 3;

 try_again:
  status = nl_sendreq(sd, request, NLM_F_ROOT|NLM_F_MATCH, &seq);
  if (status < 0)
    return status;
  if (seq == 0)
    seq = (int)time(NULL);
  while(!done){
    struct pollfd pfd;

    pfd.fd = sd;
    pfd.events = POLLIN | POLLPRI;
    pfd.revents = 0;
    status = poll(&pfd, 1, 1000);
    if (status < 0)
	return status;
    else if (status == 0) {
	seq++;
	if (tries-- > 0)
	    goto try_again;
	return -1;
    }

    status = nl_getmsg(sd, request, seq, &nlh, &done);
    if (status < 0)
      return status;
    if (nlh){
      struct nlmsg_list *nlm_next = (struct nlmsg_list *)malloc(sizeof(struct nlmsg_list));
      if (nlm_next == NULL){
	int saved_errno = errno;
	free(nlh);
	__set_errno(saved_errno);
	status = -1;
      } else {
	nlm_next->nlm_next = NULL;
	nlm_next->nlh = (struct nlmsghdr *)nlh;
	nlm_next->size = status;
	nlm_next->seq = seq;
	if (*nlm_list == NULL){
	  *nlm_list = nlm_next;
	  *nlm_end = nlm_next;
	} else {
	  (*nlm_end)->nlm_next = nlm_next;
	  *nlm_end = nlm_next;
	}
      }
    }
  }
  return status >= 0 ? seq : status;
}