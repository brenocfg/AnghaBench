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
struct sockaddr {scalar_t__ sa_family; int /*<<< orphan*/  sa_len; } ;
struct rt_msghdr {int rtm_addrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ROUNDUP (int /*<<< orphan*/ ) ; 
 int RTAX_MAX ; 

void
route_ParseHdr(struct rt_msghdr *rtm, struct sockaddr *sa[RTAX_MAX])
{
  char *wp;
  int rtax;

  wp = (char *)(rtm + 1);

  for (rtax = 0; rtax < RTAX_MAX; rtax++)
    if (rtm->rtm_addrs & (1 << rtax)) {
      sa[rtax] = (struct sockaddr *)wp;
      wp += ROUNDUP(sa[rtax]->sa_len);
      if (sa[rtax]->sa_family == 0)
        sa[rtax] = NULL;	/* ??? */
    } else
      sa[rtax] = NULL;
}