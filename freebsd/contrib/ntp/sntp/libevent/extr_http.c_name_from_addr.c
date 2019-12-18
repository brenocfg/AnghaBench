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
typedef  int /*<<< orphan*/  strport ;
typedef  int /*<<< orphan*/  ntop ;
typedef  int /*<<< orphan*/  ev_socklen_t ;

/* Variables and functions */
 int EAI_SYSTEM ; 
 int NI_MAXHOST ; 
 int NI_MAXSERV ; 
 int NI_NUMERICHOST ; 
 int NI_NUMERICSERV ; 
 int /*<<< orphan*/  event_err (int,char*) ; 
 int /*<<< orphan*/  event_errx (int,char*,int /*<<< orphan*/ ) ; 
 int fake_getnameinfo (struct sockaddr*,int /*<<< orphan*/ ,char*,int,char*,int,int) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int getnameinfo (struct sockaddr*,int /*<<< orphan*/ ,char*,int,char*,int,int) ; 
 char* mm_strdup (char*) ; 

__attribute__((used)) static void
name_from_addr(struct sockaddr *sa, ev_socklen_t salen,
    char **phost, char **pport)
{
	char ntop[NI_MAXHOST];
	char strport[NI_MAXSERV];
	int ni_result;

#ifdef EVENT__HAVE_GETNAMEINFO
	ni_result = getnameinfo(sa, salen,
		ntop, sizeof(ntop), strport, sizeof(strport),
		NI_NUMERICHOST|NI_NUMERICSERV);

	if (ni_result != 0) {
#ifdef EAI_SYSTEM
		/* Windows doesn't have an EAI_SYSTEM. */
		if (ni_result == EAI_SYSTEM)
			event_err(1, "getnameinfo failed");
		else
#endif
			event_errx(1, "getnameinfo failed: %s", gai_strerror(ni_result));
		return;
	}
#else
	ni_result = fake_getnameinfo(sa, salen,
		ntop, sizeof(ntop), strport, sizeof(strport),
		NI_NUMERICHOST|NI_NUMERICSERV);
	if (ni_result != 0)
			return;
#endif

	*phost = mm_strdup(ntop);
	*pport = mm_strdup(strport);
}