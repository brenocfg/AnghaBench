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
struct nlmsg_list {struct nlmsg_list* nlm_next; struct nlmsg_list* nlh; } ;

/* Variables and functions */
 int /*<<< orphan*/  __set_errno (int) ; 
 int errno ; 
 int /*<<< orphan*/  free (struct nlmsg_list*) ; 

__attribute__((used)) static void
free_nlmsglist(struct nlmsg_list *nlm0)
{
  struct nlmsg_list *nlm, *nlm_next;
  int saved_errno;
  if (!nlm0)
    return;
  saved_errno = errno;
  for (nlm=nlm0; nlm; nlm=nlm_next){
    if (nlm->nlh)
      free(nlm->nlh);
    nlm_next=nlm->nlm_next;
    free(nlm);
  }
  __set_errno(saved_errno);
}