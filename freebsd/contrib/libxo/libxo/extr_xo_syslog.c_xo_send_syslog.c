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
struct iovec {char* iov_base; int iov_len; } ;

/* Variables and functions */
 scalar_t__ CONNPRIV ; 
 scalar_t__ ENOBUFS ; 
 int LOG_CONS ; 
 int LOG_NDELAY ; 
 int O_CLOEXEC ; 
 int O_NONBLOCK ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  REAL_VOID (int /*<<< orphan*/ ) ; 
 int STDERR_FILENO ; 
 int /*<<< orphan*/  _PATH_CONSOLE ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int open (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ send (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 void* strlen (char*) ; 
 int /*<<< orphan*/  usleep (int) ; 
 int /*<<< orphan*/  writev (int,struct iovec*,int) ; 
 int /*<<< orphan*/  xo_connect_log () ; 
 int /*<<< orphan*/  xo_disconnect_log () ; 
 int /*<<< orphan*/  xo_logfile ; 
 int xo_logstat ; 
 int /*<<< orphan*/  xo_logtag ; 
 int /*<<< orphan*/  xo_open_log_unlocked (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xo_opened ; 
 scalar_t__ xo_status ; 
 int /*<<< orphan*/  xo_syslog_send (char*,char*,char*) ; 

__attribute__((used)) static void
xo_send_syslog (char *full_msg, char *v0_hdr,
		char *text_only)
{
    if (xo_syslog_send) {
	xo_syslog_send(full_msg, v0_hdr, text_only);
	return;
    }

    int fd;
    int full_len = strlen(full_msg);

    /* Output to stderr if requested, then we've been passed a v0 header */
    if (v0_hdr) {
        struct iovec iov[3];
        struct iovec *v = iov;
        char newline[] = "\n";

        v->iov_base = v0_hdr;
        v->iov_len = strlen(v0_hdr);
        v += 1;
        v->iov_base = text_only;
        v->iov_len = strlen(text_only);
        v += 1;
        v->iov_base = newline;
        v->iov_len = 1;
        v += 1;
        REAL_VOID(writev(STDERR_FILENO, iov, 3));
    }

    /* Get connected, output the message to the local logger. */
    if (!xo_opened)
        xo_open_log_unlocked(xo_logtag, xo_logstat | LOG_NDELAY, 0);
    xo_connect_log();

    /*
     * If the send() fails, there are two likely scenarios: 
     *  1) syslogd was restarted
     *  2) /var/run/log is out of socket buffer space, which
     *     in most cases means local DoS.
     * If the error does not indicate a full buffer, we address
     * case #1 by attempting to reconnect to /var/run/log[priv]
     * and resending the message once.
     *
     * If we are working with a privileged socket, the retry
     * attempts end there, because we don't want to freeze a
     * critical application like su(1) or sshd(8).
     *
     * Otherwise, we address case #2 by repeatedly retrying the
     * send() to give syslogd a chance to empty its socket buffer.
     */

    if (send(xo_logfile, full_msg, full_len, 0) < 0) {
        if (errno != ENOBUFS) {
            /*
             * Scenario 1: syslogd was restarted
             * reconnect and resend once
             */
            xo_disconnect_log();
            xo_connect_log();
            if (send(xo_logfile, full_msg, full_len, 0) >= 0) {
                return;
            }
            /*
             * if the resend failed, fall through to
             * possible scenario 2
             */
        }
        while (errno == ENOBUFS) {
            /*
             * Scenario 2: out of socket buffer space
             * possible DoS, fail fast on a privileged
             * socket
             */
            if (xo_status == CONNPRIV)
                break;
            usleep(1);
            if (send(xo_logfile, full_msg, full_len, 0) >= 0) {
                return;
            }
        }
    } else {
        return;
    }

    /*
     * Output the message to the console; try not to block
     * as a blocking console should not stop other processes.
     * Make sure the error reported is the one from the syslogd failure.
     */
    int flags = O_WRONLY | O_NONBLOCK;
#ifdef O_CLOEXEC
    flags |= O_CLOEXEC;
#endif /* O_CLOEXEC */

    if (xo_logstat & LOG_CONS
        && (fd = open(_PATH_CONSOLE, flags, 0)) >= 0) {
        struct iovec iov[2];
        struct iovec *v = iov;
        char crnl[] = "\r\n";
	char *p;

        p = strchr(full_msg, '>') + 1;
        v->iov_base = p;
        v->iov_len = full_len - (p - full_msg);
        ++v;
        v->iov_base = crnl;
        v->iov_len = 2;
        REAL_VOID(writev(fd, iov, 2));
        (void) close(fd);
    }
}