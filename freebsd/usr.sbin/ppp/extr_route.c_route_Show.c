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
struct sockaddr {int dummy; } ;
struct rt_msghdr {int /*<<< orphan*/  rtm_index; int /*<<< orphan*/  rtm_flags; int /*<<< orphan*/  rtm_msglen; } ;
struct cmdargs {int /*<<< orphan*/  prompt; } ;

/* Variables and functions */
 int CTL_NET ; 
 int /*<<< orphan*/  Index2Nam (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LogERROR ; 
 int NET_RT_DUMP ; 
 int PF_ROUTE ; 
 size_t RTAX_DST ; 
 size_t RTAX_GATEWAY ; 
 int RTAX_MAX ; 
 size_t RTAX_NETMASK ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  p_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  p_sockaddr (int /*<<< orphan*/ ,struct sockaddr*,struct sockaddr*,int) ; 
 int /*<<< orphan*/  prompt_Printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  route_ParseHdr (struct rt_msghdr*,struct sockaddr**) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ sysctl (int*,int,char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
route_Show(struct cmdargs const *arg)
{
  struct rt_msghdr *rtm;
  struct sockaddr *sa[RTAX_MAX];
  char *sp, *ep, *cp;
  size_t needed;
  int mib[6];

  mib[0] = CTL_NET;
  mib[1] = PF_ROUTE;
  mib[2] = 0;
  mib[3] = 0;
  mib[4] = NET_RT_DUMP;
  mib[5] = 0;
  if (sysctl(mib, 6, NULL, &needed, NULL, 0) < 0) {
    log_Printf(LogERROR, "route_Show: sysctl: estimate: %s\n", strerror(errno));
    return (1);
  }
  sp = malloc(needed);
  if (sp == NULL)
    return (1);
  if (sysctl(mib, 6, sp, &needed, NULL, 0) < 0) {
    log_Printf(LogERROR, "route_Show: sysctl: getroute: %s\n", strerror(errno));
    free(sp);
    return (1);
  }
  ep = sp + needed;

  prompt_Printf(arg->prompt, "%-20s%-20sFlags  Netif\n",
                "Destination", "Gateway");
  for (cp = sp; cp < ep; cp += rtm->rtm_msglen) {
    rtm = (struct rt_msghdr *)cp;

    route_ParseHdr(rtm, sa);

    if (sa[RTAX_DST] && sa[RTAX_GATEWAY]) {
      p_sockaddr(arg->prompt, sa[RTAX_DST], sa[RTAX_NETMASK], 20);
      p_sockaddr(arg->prompt, sa[RTAX_GATEWAY], NULL, 20);

      p_flags(arg->prompt, rtm->rtm_flags, 6);
      prompt_Printf(arg->prompt, " %s\n", Index2Nam(rtm->rtm_index));
    } else
      prompt_Printf(arg->prompt, "<can't parse routing entry>\n");
  }
  free(sp);
  return 0;
}