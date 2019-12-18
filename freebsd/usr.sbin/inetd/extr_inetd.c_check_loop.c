#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int /*<<< orphan*/  sa_len; } ;
struct TYPE_6__ {int /*<<< orphan*/  sin6_port; } ;
struct TYPE_5__ {int /*<<< orphan*/  sin_port; } ;
struct servtab {scalar_t__ se_socktype; int se_family; int /*<<< orphan*/  se_proto; int /*<<< orphan*/  se_service; TYPE_2__ se_ctrladdr6; TYPE_1__ se_ctrladdr4; int /*<<< orphan*/  se_bi; struct servtab* se_next; } ;
typedef  int /*<<< orphan*/  pname ;
struct TYPE_8__ {int /*<<< orphan*/  sin_port; } ;
struct TYPE_7__ {int /*<<< orphan*/  sin6_port; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  LOG_WARNING ; 
 int NI_MAXHOST ; 
 int /*<<< orphan*/  NI_NUMERICHOST ; 
 scalar_t__ SOCK_DGRAM ; 
 TYPE_4__* csatosin (struct sockaddr const*) ; 
 TYPE_3__* csatosin6 (struct sockaddr const*) ; 
 int /*<<< orphan*/  getnameinfo (struct sockaddr const*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct servtab* servtab ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

int
check_loop(const struct sockaddr *sa, const struct servtab *sep)
{
	struct servtab *se2;
	char pname[NI_MAXHOST];

	for (se2 = servtab; se2; se2 = se2->se_next) {
		if (!se2->se_bi || se2->se_socktype != SOCK_DGRAM)
			continue;

		switch (se2->se_family) {
		case AF_INET:
			if (csatosin(sa)->sin_port ==
			    se2->se_ctrladdr4.sin_port)
				goto isloop;
			continue;
#ifdef INET6
		case AF_INET6:
			if (csatosin6(sa)->sin6_port ==
			    se2->se_ctrladdr6.sin6_port)
				goto isloop;
			continue;
#endif
		default:
			continue;
		}
	isloop:
		getnameinfo(sa, sa->sa_len, pname, sizeof(pname), NULL, 0,
			    NI_NUMERICHOST);
		syslog(LOG_WARNING, "%s/%s:%s/%s loop request REFUSED from %s",
		       sep->se_service, sep->se_proto,
		       se2->se_service, se2->se_proto,
		       pname);
		return 1;
	}
	return 0;
}