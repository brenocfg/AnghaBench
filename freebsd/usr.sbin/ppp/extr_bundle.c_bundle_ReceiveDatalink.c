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
struct msghdr {int msg_iovlen; char* msg_control; int msg_controllen; struct iovec* msg_iov; scalar_t__ msg_namelen; int /*<<< orphan*/ * msg_name; } ;
struct iovec {int /*<<< orphan*/ * iov_base; scalar_t__ iov_len; } ;
struct datalink {int /*<<< orphan*/  bundle; } ;
struct cmsghdr {int cmsg_len; scalar_t__ cmsg_level; scalar_t__ cmsg_type; } ;
struct bundle {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int caddr_t ;

/* Variables and functions */
 scalar_t__ CMSG_DATA (struct cmsghdr*) ; 
 int /*<<< orphan*/  LogDEBUG ; 
 int /*<<< orphan*/  LogERROR ; 
 int /*<<< orphan*/  LogPHASE ; 
 int /*<<< orphan*/  LogWARN ; 
 int /*<<< orphan*/  MSG_WAITALL ; 
 int SCATTER_SEGMENTS ; 
 scalar_t__ SCM_RIGHTS ; 
 int SEND_MAXFD ; 
 scalar_t__ SOL_SOCKET ; 
 int /*<<< orphan*/  Version ; 
 int /*<<< orphan*/  bundle_CalculateBandwidth (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bundle_DatalinkLinkin (struct bundle*,struct datalink*) ; 
 int /*<<< orphan*/  close (int) ; 
 int datalink2iov (int /*<<< orphan*/ *,struct iovec*,int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  datalink_AuthOk (struct datalink*) ; 
 int /*<<< orphan*/  datalink_Destroy (struct datalink*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getpid () ; 
 struct datalink* iov2datalink (struct bundle*,struct iovec*,int*,int,int,int*,int*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * malloc (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct msghdr*,char,int) ; 
 int readv (int,struct iovec*,int) ; 
 int recvmsg (int,struct msghdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int write (int,int /*<<< orphan*/ *,int) ; 

void
bundle_ReceiveDatalink(struct bundle *bundle, int s)
{
  char cmsgbuf[sizeof(struct cmsghdr) + sizeof(int) * SEND_MAXFD];
  int niov, expect, f, *fd, nfd, onfd;
  ssize_t got;
  struct iovec iov[SCATTER_SEGMENTS];
  struct cmsghdr *cmsg;
  struct msghdr msg;
  struct datalink *dl;
  pid_t pid;

  log_Printf(LogPHASE, "Receiving datalink\n");

  /*
   * Create our scatter/gather array - passing NULL gets the space
   * allocation requirement rather than actually flattening the
   * structures.
   */
  iov[0].iov_len = strlen(Version) + 1;
  iov[0].iov_base = NULL;
  niov = 1;
  if (datalink2iov(NULL, iov, &niov, SCATTER_SEGMENTS, NULL, NULL) == -1) {
    log_Printf(LogERROR, "Cannot determine space required for link\n");
    return;
  }

  /* Allocate the scatter/gather array for recvmsg() */
  for (f = expect = 0; f < niov; f++) {
    if ((iov[f].iov_base = malloc(iov[f].iov_len)) == NULL) {
      log_Printf(LogERROR, "Cannot allocate space to receive link\n");
      return;
    }
    if (f)
      expect += iov[f].iov_len;
  }

  /* Set up our message */
  cmsg = (struct cmsghdr *)cmsgbuf;
  cmsg->cmsg_len = sizeof cmsgbuf;
  cmsg->cmsg_level = SOL_SOCKET;
  cmsg->cmsg_type = 0;

  memset(&msg, '\0', sizeof msg);
  msg.msg_name = NULL;
  msg.msg_namelen = 0;
  msg.msg_iov = iov;
  msg.msg_iovlen = 1;		/* Only send the version at the first pass */
  msg.msg_control = cmsgbuf;
  msg.msg_controllen = sizeof cmsgbuf;

  log_Printf(LogDEBUG, "Expecting %u scatter/gather bytes\n",
             (unsigned)iov[0].iov_len);

  if ((got = recvmsg(s, &msg, MSG_WAITALL)) != (ssize_t)iov[0].iov_len) {
    if (got == -1)
      log_Printf(LogERROR, "Failed recvmsg: %s\n", strerror(errno));
    else
      log_Printf(LogERROR, "Failed recvmsg: Got %zd, not %u\n",
                 got, (unsigned)iov[0].iov_len);
    while (niov--)
      free(iov[niov].iov_base);
    return;
  }

  if (cmsg->cmsg_level != SOL_SOCKET || cmsg->cmsg_type != SCM_RIGHTS) {
    log_Printf(LogERROR, "Recvmsg: no descriptors received !\n");
    while (niov--)
      free(iov[niov].iov_base);
    return;
  }

  fd = (int *)CMSG_DATA(cmsg);
  nfd = ((caddr_t)cmsg + cmsg->cmsg_len - (caddr_t)fd) / sizeof(int);

  if (nfd < 2) {
    log_Printf(LogERROR, "Recvmsg: %d descriptor%s received (too few) !\n",
               nfd, nfd == 1 ? "" : "s");
    while (nfd--)
      close(fd[nfd]);
    while (niov--)
      free(iov[niov].iov_base);
    return;
  }

  /*
   * We've successfully received two or more open file descriptors
   * through our socket, plus a version string.  Make sure it's the
   * correct version, and drop the connection if it's not.
   */
  if (strncmp(Version, iov[0].iov_base, iov[0].iov_len)) {
    log_Printf(LogWARN, "Cannot receive datalink, incorrect version"
               " (\"%.*s\", not \"%s\")\n", (int)iov[0].iov_len,
               (char *)iov[0].iov_base, Version);
    while (nfd--)
      close(fd[nfd]);
    while (niov--)
      free(iov[niov].iov_base);
    return;
  }

  /*
   * Everything looks good.  Send the other side our process id so that
   * they can transfer lock ownership, and wait for them to send the
   * actual link data.
   */
  pid = getpid();
  if ((got = write(fd[1], &pid, sizeof pid)) != sizeof pid) {
    if (got == -1)
      log_Printf(LogERROR, "Failed write: %s\n", strerror(errno));
    else
      log_Printf(LogERROR, "Failed write: Got %zd, not %d\n", got,
                 (int)(sizeof pid));
    while (nfd--)
      close(fd[nfd]);
    while (niov--)
      free(iov[niov].iov_base);
    return;
  }

  if ((got = readv(fd[1], iov + 1, niov - 1)) != expect) {
    if (got == -1)
      log_Printf(LogERROR, "Failed write: %s\n", strerror(errno));
    else
      log_Printf(LogERROR, "Failed write: Got %zd, not %d\n", got, expect);
    while (nfd--)
      close(fd[nfd]);
    while (niov--)
      free(iov[niov].iov_base);
    return;
  }
  close(fd[1]);

  onfd = nfd;	/* We've got this many in our array */
  nfd -= 2;	/* Don't include p->fd and our reply descriptor */
  niov = 1;	/* Skip the version id */
  dl = iov2datalink(bundle, iov, &niov, sizeof iov / sizeof *iov, fd[0],
                    fd + 2, &nfd);
  if (dl) {

    if (nfd) {
      log_Printf(LogERROR, "bundle_ReceiveDatalink: Failed to handle %d "
                 "auxiliary file descriptors (%d remain)\n", onfd, nfd);
      datalink_Destroy(dl);
      while (nfd--)
        close(fd[onfd--]);
      close(fd[0]);
    } else {
      bundle_DatalinkLinkin(bundle, dl);
      datalink_AuthOk(dl);
      bundle_CalculateBandwidth(dl->bundle);
    }
  } else {
    while (nfd--)
      close(fd[onfd--]);
    close(fd[0]);
    close(fd[1]);
  }

  free(iov[0].iov_base);
}