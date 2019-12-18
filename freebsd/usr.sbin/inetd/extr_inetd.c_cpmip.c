#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int time_t ;
struct sockaddr_storage {int ss_family; } ;
struct sockaddr_in6 {int sin6_family; int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_6__ {scalar_t__ s_addr; } ;
struct sockaddr_in {int sin_family; TYPE_1__ sin_addr; } ;
struct sockaddr {int /*<<< orphan*/  sa_len; } ;
struct servtab {int se_maxcpm; int se_family; int /*<<< orphan*/  se_service; } ;
struct in_addr {int dummy; } ;
struct in6_addr {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  rss ;
typedef  int /*<<< orphan*/  pname ;
struct TYPE_8__ {int ch_Family; scalar_t__ ch_LTime; TYPE_2__* ch_Times; int /*<<< orphan*/ * ch_Service; int /*<<< orphan*/  ch_Addr6; TYPE_1__ ch_Addr4; } ;
struct TYPE_7__ {unsigned int ct_Ticks; scalar_t__ ct_Count; } ;
typedef  TYPE_2__ CTime ;
typedef  TYPE_3__ CHash ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 unsigned int CHTGRAN ; 
 unsigned int CHTSIZE ; 
 TYPE_3__* CHashAry ; 
 int CPMHMASK ; 
 scalar_t__ IN6_ARE_ADDR_EQUAL (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int NI_MAXHOST ; 
 int /*<<< orphan*/  NI_NUMERICHOST ; 
 int /*<<< orphan*/  bzero (TYPE_2__*,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getnameinfo (struct sockaddr*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ getpeername (int,struct sockaddr*,int*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int) ; 
 unsigned int time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
cpmip(const struct servtab *sep, int ctrl)
{
	struct sockaddr_storage rss;
	socklen_t rssLen = sizeof(rss);
	int r = 0;

	/*
	 * If getpeername() fails, just let it through (if logging is
	 * enabled the condition is caught elsewhere)
	 */

	if (sep->se_maxcpm > 0 && 
	   (sep->se_family == AF_INET || sep->se_family == AF_INET6) &&
	    getpeername(ctrl, (struct sockaddr *)&rss, &rssLen) == 0 ) {
		time_t t = time(NULL);
		int hv = 0xABC3D20F;
		int i;
		int cnt = 0;
		CHash *chBest = NULL;
		unsigned int ticks = t / CHTGRAN;
		struct sockaddr_in *sin4;
#ifdef INET6
		struct sockaddr_in6 *sin6;
#endif

		sin4 = (struct sockaddr_in *)&rss;
#ifdef INET6
		sin6 = (struct sockaddr_in6 *)&rss;
#endif
		{
			char *p;
			int addrlen;

			switch (rss.ss_family) {
			case AF_INET:
				p = (char *)&sin4->sin_addr;
				addrlen = sizeof(struct in_addr);
				break;
#ifdef INET6
			case AF_INET6:
				p = (char *)&sin6->sin6_addr;
				addrlen = sizeof(struct in6_addr);
				break;
#endif
			default:
				/* should not happen */
				return -1;
			}

			for (i = 0; i < addrlen; ++i, ++p) {
				hv = (hv << 5) ^ (hv >> 23) ^ *p;
			}
			hv = (hv ^ (hv >> 16));
		}
		for (i = 0; i < 5; ++i) {
			CHash *ch = &CHashAry[(hv + i) & CPMHMASK];

			if (rss.ss_family == AF_INET &&
			    ch->ch_Family == AF_INET &&
			    sin4->sin_addr.s_addr == ch->ch_Addr4.s_addr &&
			    ch->ch_Service && strcmp(sep->se_service,
			    ch->ch_Service) == 0) {
				chBest = ch;
				break;
			}
#ifdef INET6
			if (rss.ss_family == AF_INET6 &&
			    ch->ch_Family == AF_INET6 &&
			    IN6_ARE_ADDR_EQUAL(&sin6->sin6_addr,
					       &ch->ch_Addr6) != 0 &&
			    ch->ch_Service && strcmp(sep->se_service,
			    ch->ch_Service) == 0) {
				chBest = ch;
				break;
			}
#endif
			if (chBest == NULL || ch->ch_LTime == 0 || 
			    ch->ch_LTime < chBest->ch_LTime) {
				chBest = ch;
			}
		}
		if ((rss.ss_family == AF_INET &&
		     (chBest->ch_Family != AF_INET ||
		      sin4->sin_addr.s_addr != chBest->ch_Addr4.s_addr)) ||
		    chBest->ch_Service == NULL ||
		    strcmp(sep->se_service, chBest->ch_Service) != 0) {
			chBest->ch_Family = sin4->sin_family;
			chBest->ch_Addr4 = sin4->sin_addr;
			if (chBest->ch_Service)
				free(chBest->ch_Service);
			chBest->ch_Service = strdup(sep->se_service);
			bzero(chBest->ch_Times, sizeof(chBest->ch_Times));
		} 
#ifdef INET6
		if ((rss.ss_family == AF_INET6 &&
		     (chBest->ch_Family != AF_INET6 ||
		      IN6_ARE_ADDR_EQUAL(&sin6->sin6_addr,
					 &chBest->ch_Addr6) == 0)) ||
		    chBest->ch_Service == NULL ||
		    strcmp(sep->se_service, chBest->ch_Service) != 0) {
			chBest->ch_Family = sin6->sin6_family;
			chBest->ch_Addr6 = sin6->sin6_addr;
			if (chBest->ch_Service)
				free(chBest->ch_Service);
			chBest->ch_Service = strdup(sep->se_service);
			bzero(chBest->ch_Times, sizeof(chBest->ch_Times));
		}
#endif
		chBest->ch_LTime = t;
		{
			CTime *ct = &chBest->ch_Times[ticks % CHTSIZE];
			if (ct->ct_Ticks != ticks) {
				ct->ct_Ticks = ticks;
				ct->ct_Count = 0;
			}
			++ct->ct_Count;
		}
		for (i = 0; i < CHTSIZE; ++i) {
			CTime *ct = &chBest->ch_Times[i];
			if (ct->ct_Ticks <= ticks &&
			    ct->ct_Ticks >= ticks - CHTSIZE) {
				cnt += ct->ct_Count;
			}
		}
		if ((cnt * 60) / (CHTSIZE * CHTGRAN) > sep->se_maxcpm) {
			char pname[NI_MAXHOST];

			getnameinfo((struct sockaddr *)&rss,
				    ((struct sockaddr *)&rss)->sa_len,
				    pname, sizeof(pname), NULL, 0,
				    NI_NUMERICHOST);
			r = -1;
			syslog(LOG_ERR,
			    "%s from %s exceeded counts/min (limit %d/min)",
			    sep->se_service, pname,
			    sep->se_maxcpm);
		}
	}
	return(r);
}