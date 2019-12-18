#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct utmpx {int /*<<< orphan*/  ut_syslen; scalar_t__* ut_addr_v6; int /*<<< orphan*/  ut_addr; int /*<<< orphan*/  ut_host; int /*<<< orphan*/  ut_user; int /*<<< orphan*/  ut_pid; int /*<<< orphan*/  ut_line; int /*<<< orphan*/  ut_type; int /*<<< orphan*/  ut_id; } ;
struct TYPE_10__ {int /*<<< orphan*/  s6_addr; } ;
struct sockaddr_in6 {TYPE_5__ sin6_addr; } ;
struct TYPE_8__ {scalar_t__ sa_family; } ;
struct TYPE_6__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_7__ {TYPE_1__ sin_addr; } ;
struct TYPE_9__ {TYPE_3__ sa; TYPE_2__ sa_in; } ;
struct logininfo {int type; int /*<<< orphan*/  hostname; TYPE_4__ hostaddr; int /*<<< orphan*/  username; int /*<<< orphan*/  pid; int /*<<< orphan*/  line; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  DEAD_PROCESS ; 
 scalar_t__ IN6_IS_ADDR_V4MAPPED (TYPE_5__*) ; 
#define  LTYPE_LOGIN 129 
#define  LTYPE_LOGOUT 128 
 int /*<<< orphan*/  MIN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MIN_SIZEOF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USER_PROCESS ; 
 int /*<<< orphan*/  line_abbrevname (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  line_stripname (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct utmpx*,char,int) ; 
 int /*<<< orphan*/  set_utmpx_time (struct logininfo*,struct utmpx*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
construct_utmpx(struct logininfo *li, struct utmpx *utx)
{
# ifdef HAVE_ADDR_V6_IN_UTMP
	struct sockaddr_in6 *sa6;
#  endif
	memset(utx, '\0', sizeof(*utx));

# ifdef HAVE_ID_IN_UTMPX
	line_abbrevname(utx->ut_id, li->line, sizeof(utx->ut_id));
# endif

	/* this is done here to keep utmp constants out of loginrec.h */
	switch (li->type) {
	case LTYPE_LOGIN:
		utx->ut_type = USER_PROCESS;
		break;
	case LTYPE_LOGOUT:
		utx->ut_type = DEAD_PROCESS;
		break;
	}
	line_stripname(utx->ut_line, li->line, sizeof(utx->ut_line));
	set_utmpx_time(li, utx);
	utx->ut_pid = li->pid;

	/* strncpy(): Don't necessarily want null termination */
	strncpy(utx->ut_user, li->username,
	    MIN_SIZEOF(utx->ut_user, li->username));

	if (li->type == LTYPE_LOGOUT)
		return;

	/*
	 * These fields are only used when logging in, and are blank
	 * for logouts.
	 */

# ifdef HAVE_HOST_IN_UTMPX
	strncpy(utx->ut_host, li->hostname,
	    MIN_SIZEOF(utx->ut_host, li->hostname));
# endif
# ifdef HAVE_ADDR_IN_UTMPX
	/* this is just a 32-bit IP address */
	if (li->hostaddr.sa.sa_family == AF_INET)
		utx->ut_addr = li->hostaddr.sa_in.sin_addr.s_addr;
# endif
# ifdef HAVE_ADDR_V6_IN_UTMP
	/* this is just a 128-bit IPv6 address */
	if (li->hostaddr.sa.sa_family == AF_INET6) {
		sa6 = ((struct sockaddr_in6 *)&li->hostaddr.sa);
		memcpy(utx->ut_addr_v6, sa6->sin6_addr.s6_addr, 16);
		if (IN6_IS_ADDR_V4MAPPED(&sa6->sin6_addr)) {
			utx->ut_addr_v6[0] = utx->ut_addr_v6[3];
			utx->ut_addr_v6[1] = 0;
			utx->ut_addr_v6[2] = 0;
			utx->ut_addr_v6[3] = 0;
		}
	}
# endif
# ifdef HAVE_SYSLEN_IN_UTMPX
	/* ut_syslen is the length of the utx_host string */
	utx->ut_syslen = MIN(strlen(li->hostname), sizeof(utx->ut_host));
# endif
}