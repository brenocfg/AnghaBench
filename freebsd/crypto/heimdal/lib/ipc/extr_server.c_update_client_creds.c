#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uid_t ;
typedef  int /*<<< orphan*/  ucred_t ;
struct xucred {scalar_t__ cr_version; scalar_t__ cr_uid; scalar_t__ cr_pid; int /*<<< orphan*/  cr_gid; } ;
struct ucred {scalar_t__ uid; scalar_t__ pid; int /*<<< orphan*/  gid; } ;
struct sockcred {scalar_t__ sc_euid; int /*<<< orphan*/  sc_egid; } ;
typedef  void msghdr ;
struct cmsghdr {scalar_t__ cmsg_level; scalar_t__ cmsg_type; } ;
struct TYPE_2__ {scalar_t__ uid; scalar_t__ pid; int /*<<< orphan*/  gid; } ;
struct client {TYPE_1__ unixrights; int /*<<< orphan*/  fd; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  peercred ;
typedef  int /*<<< orphan*/  pc ;
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMGROUP_MAX ; 
 scalar_t__ CMSG_DATA (struct cmsghdr*) ; 
 struct cmsghdr* CMSG_FIRSTHDR (void*) ; 
 int CMSG_SPACE (int /*<<< orphan*/ ) ; 
 scalar_t__ LOCAL_PEERCRED ; 
 int MSG_CTRUNC ; 
 scalar_t__ SCM_CREDS ; 
 int /*<<< orphan*/  SOCKCREDSIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ SOL_SOCKET ; 
 int SO_PEERCRED ; 
 scalar_t__ XUCRED_VERSION ; 
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ getpeereid (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ getpeerucred (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ getsockopt (int /*<<< orphan*/ ,scalar_t__,int,void*,int*) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ recvmsg (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucred_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucred_getegid (int /*<<< orphan*/ *) ; 
 scalar_t__ ucred_geteuid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
update_client_creds(struct client *c)
{
#ifdef HAVE_GETPEERUCRED
    /* Solaris 10 */
    {
	ucred_t *peercred;

	if (getpeerucred(c->fd, &peercred) != 0) {
	    c->unixrights.uid = ucred_geteuid(peercred);
	    c->unixrights.gid = ucred_getegid(peercred);
	    c->unixrights.pid = 0;
	    ucred_free(peercred);
	    return 1;
	}
    }
#endif
#ifdef HAVE_GETPEEREID
    /* FreeBSD, OpenBSD */
    {
	uid_t uid;
	gid_t gid;

	if (getpeereid(c->fd, &uid, &gid) == 0) {
	    c->unixrights.uid = uid;
	    c->unixrights.gid = gid;
	    c->unixrights.pid = 0;
	    return 1;
	}
    }
#endif
#ifdef SO_PEERCRED
    /* Linux */
    {
	struct ucred pc;
	socklen_t pclen = sizeof(pc);

	if (getsockopt(c->fd, SOL_SOCKET, SO_PEERCRED, (void *)&pc, &pclen) == 0) {
	    c->unixrights.uid = pc.uid;
	    c->unixrights.gid = pc.gid;
	    c->unixrights.pid = pc.pid;
	    return 1;
	}
    }
#endif
#if defined(LOCAL_PEERCRED) && defined(XUCRED_VERSION)
    {
	struct xucred peercred;
	socklen_t peercredlen = sizeof(peercred);

	if (getsockopt(c->fd, LOCAL_PEERCRED, 1,
		       (void *)&peercred, &peercredlen) == 0
	    && peercred.cr_version == XUCRED_VERSION)
	{
	    c->unixrights.uid = peercred.cr_uid;
	    c->unixrights.gid = peercred.cr_gid;
	    c->unixrights.pid = peercred.cr_pid;
	    return 1;
	}
    }
#endif
#if defined(SOCKCREDSIZE) && defined(SCM_CREDS)
    /* NetBSD */
    if (c->unixrights.uid == (uid_t)-1) {
	struct msghdr msg;
	socklen_t crmsgsize;
	void *crmsg;
	struct cmsghdr *cmp;
	struct sockcred *sc;

	memset(&msg, 0, sizeof(msg));
	crmsgsize = CMSG_SPACE(SOCKCREDSIZE(CMGROUP_MAX));
	if (crmsgsize == 0)
	    return 1 ;

	crmsg = malloc(crmsgsize);
	if (crmsg == NULL)
	    goto failed_scm_creds;

	memset(crmsg, 0, crmsgsize);

	msg.msg_control = crmsg;
	msg.msg_controllen = crmsgsize;

	if (recvmsg(c->fd, &msg, 0) < 0) {
	    free(crmsg);
	    goto failed_scm_creds;
	}

	if (msg.msg_controllen == 0 || (msg.msg_flags & MSG_CTRUNC) != 0) {
	    free(crmsg);
	    goto failed_scm_creds;
	}

	cmp = CMSG_FIRSTHDR(&msg);
	if (cmp->cmsg_level != SOL_SOCKET || cmp->cmsg_type != SCM_CREDS) {
	    free(crmsg);
	    goto failed_scm_creds;
	}

	sc = (struct sockcred *)(void *)CMSG_DATA(cmp);

	c->unixrights.uid = sc->sc_euid;
	c->unixrights.gid = sc->sc_egid;
	c->unixrights.pid = 0;

	free(crmsg);
	return 1;
    } else {
	/* we already got the cred, just return it */
	return 1;
    }
 failed_scm_creds:
#endif
    return 0;
}