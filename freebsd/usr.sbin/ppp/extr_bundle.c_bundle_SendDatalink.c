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
struct sockaddr_un {int /*<<< orphan*/  sun_path; } ;
struct msghdr {int msg_iovlen; char* msg_control; int msg_controllen; scalar_t__ msg_flags; struct iovec* msg_iov; scalar_t__ msg_namelen; int /*<<< orphan*/ * msg_name; } ;
struct iovec {int /*<<< orphan*/  iov_base; scalar_t__ iov_len; } ;
struct datalink {int /*<<< orphan*/  bundle; int /*<<< orphan*/  physical; int /*<<< orphan*/  name; } ;
struct cmsghdr {int cmsg_len; int /*<<< orphan*/  cmsg_type; int /*<<< orphan*/  cmsg_level; } ;
typedef  int ssize_t ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 scalar_t__ CMSG_DATA (struct cmsghdr*) ; 
 int CMSG_SPACE (int) ; 
 scalar_t__ Enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ID0uu_lock_txfr (char*,scalar_t__) ; 
 int /*<<< orphan*/  LogDEBUG ; 
 int /*<<< orphan*/  LogERROR ; 
 int /*<<< orphan*/  LogPHASE ; 
 int /*<<< orphan*/  OPT_KEEPSESSION ; 
 int /*<<< orphan*/  PF_UNSPEC ; 
 int SCATTER_SEGMENTS ; 
 int /*<<< orphan*/  SCM_RIGHTS ; 
 int SEND_MAXFD ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_RCVBUF ; 
 int /*<<< orphan*/  SO_SNDBUF ; 
 int UU_LOCK_OK ; 
 char const* Version ; 
 char* alloca (scalar_t__) ; 
 int /*<<< orphan*/  bundle_DatalinkLinkout (int /*<<< orphan*/ ,struct datalink*) ; 
 int /*<<< orphan*/  bundle_LinkClosed (int /*<<< orphan*/ ,struct datalink*) ; 
 int /*<<< orphan*/  bundle_setsid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int datalink2iov (struct datalink*,struct iovec*,int*,int,int*,int*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 scalar_t__ getpgrp () ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  memset (struct msghdr*,char,int) ; 
 char* physical_LockedDevice (int /*<<< orphan*/ ) ; 
 int read (int,scalar_t__*,int) ; 
 int sendmsg (int,struct msghdr*,int /*<<< orphan*/ ) ; 
 int setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int socketpair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int /*<<< orphan*/  strdup (char const*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ tcgetpgrp (int) ; 
 int /*<<< orphan*/  uu_lockerr (int) ; 
 int writev (int,struct iovec*,int) ; 

void
bundle_SendDatalink(struct datalink *dl, int s, struct sockaddr_un *sun)
{
  char cmsgbuf[CMSG_SPACE(sizeof(int) * SEND_MAXFD)];
  const char *constlock;
  char *lock;
  struct cmsghdr *cmsg;
  struct msghdr msg;
  struct iovec iov[SCATTER_SEGMENTS];
  int niov, f, expect, newsid, fd[SEND_MAXFD], nfd, reply[2];
  ssize_t got;
  pid_t newpid;

  log_Printf(LogPHASE, "Transmitting datalink %s\n", dl->name);

  /* Record the base device name for a lock transfer later */
  constlock = physical_LockedDevice(dl->physical);
  if (constlock) {
    lock = alloca(strlen(constlock) + 1);
    strcpy(lock, constlock);
  } else
    lock = NULL;

  bundle_LinkClosed(dl->bundle, dl);
  bundle_DatalinkLinkout(dl->bundle, dl);

  /* Build our scatter/gather array */
  iov[0].iov_len = strlen(Version) + 1;
  iov[0].iov_base = strdup(Version);
  niov = 1;
  nfd = 0;

  fd[0] = datalink2iov(dl, iov, &niov, SCATTER_SEGMENTS, fd + 2, &nfd);

  if (fd[0] != -1 && socketpair(AF_UNIX, SOCK_STREAM, PF_UNSPEC, reply) != -1) {
    /*
     * fd[1] is used to get the peer process id back, then to confirm that
     * we've transferred any device locks to that process id.
     */
    fd[1] = reply[1];

    nfd += 2;			/* Include fd[0] and fd[1] */
    memset(&msg, '\0', sizeof msg);

    msg.msg_name = NULL;
    msg.msg_namelen = 0;
    /*
     * Only send the version to start...  We used to send the whole lot, but
     * this caused problems with our RECVBUF size as a single link is about
     * 22k !  This way, we should bump into no limits.
     */
    msg.msg_iovlen = 1;
    msg.msg_iov = iov;
    msg.msg_control = cmsgbuf;
    msg.msg_controllen = CMSG_SPACE(sizeof(int) * nfd);
    msg.msg_flags = 0;

    cmsg = (struct cmsghdr *)cmsgbuf;
    cmsg->cmsg_len = msg.msg_controllen;
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;

    for (f = 0; f < nfd; f++)
      *((int *)CMSG_DATA(cmsg) + f) = fd[f];

    for (f = 1, expect = 0; f < niov; f++)
      expect += iov[f].iov_len;

    if (setsockopt(reply[0], SOL_SOCKET, SO_SNDBUF, &expect, sizeof(int)) == -1)
      log_Printf(LogERROR, "setsockopt(SO_RCVBUF, %d): %s\n", expect,
                 strerror(errno));
    if (setsockopt(reply[1], SOL_SOCKET, SO_RCVBUF, &expect, sizeof(int)) == -1)
      log_Printf(LogERROR, "setsockopt(SO_RCVBUF, %d): %s\n", expect,
                 strerror(errno));

    log_Printf(LogDEBUG, "Sending %d descriptor%s and %u bytes in scatter"
               "/gather array\n", nfd, nfd == 1 ? "" : "s",
               (unsigned)iov[0].iov_len);

    if ((got = sendmsg(s, &msg, 0)) == -1)
      log_Printf(LogERROR, "Failed sendmsg: %s: %s\n",
                 sun->sun_path, strerror(errno));
    else if (got != (ssize_t)iov[0].iov_len)
      log_Printf(LogERROR, "%s: Failed initial sendmsg: Only sent %zd of %u\n",
                 sun->sun_path, got, (unsigned)iov[0].iov_len);
    else {
      /* We must get the ACK before closing the descriptor ! */
      int res;

      if ((got = read(reply[0], &newpid, sizeof newpid)) == sizeof newpid) {
        log_Printf(LogDEBUG, "Received confirmation from pid %ld\n",
                   (long)newpid);
        if (lock && (res = ID0uu_lock_txfr(lock, newpid)) != UU_LOCK_OK)
            log_Printf(LogERROR, "uu_lock_txfr: %s\n", uu_lockerr(res));

        log_Printf(LogDEBUG, "Transmitting link (%d bytes)\n", expect);
        if ((got = writev(reply[0], iov + 1, niov - 1)) != expect) {
          if (got == -1)
            log_Printf(LogERROR, "%s: Failed writev: %s\n",
                       sun->sun_path, strerror(errno));
          else
            log_Printf(LogERROR, "%s: Failed writev: Wrote %zd of %d\n",
                       sun->sun_path, got, expect);
        }
      } else if (got == -1)
        log_Printf(LogERROR, "%s: Failed socketpair read: %s\n",
                   sun->sun_path, strerror(errno));
      else
        log_Printf(LogERROR, "%s: Failed socketpair read: Got %zd of %d\n",
                   sun->sun_path, got, (int)(sizeof newpid));
    }

    close(reply[0]);
    close(reply[1]);

    newsid = Enabled(dl->bundle, OPT_KEEPSESSION) ||
             tcgetpgrp(fd[0]) == getpgrp();
    while (nfd)
      close(fd[--nfd]);
    if (newsid)
      bundle_setsid(dl->bundle, got != -1);
  }
  close(s);

  while (niov--)
    free(iov[niov].iov_base);
}