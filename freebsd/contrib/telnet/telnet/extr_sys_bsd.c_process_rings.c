#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct timeval {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  fd_mask ;
struct TYPE_7__ {scalar_t__ didnetreceive; scalar_t__ gotDM; } ;
struct TYPE_6__ {char* supply; } ;

/* Variables and functions */
 int /*<<< orphan*/  Dump (char,char*,int) ; 
 scalar_t__ EINTR ; 
 scalar_t__ EINVAL ; 
 scalar_t__ EIO ; 
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  FD_CLR (int,int /*<<< orphan*/ *) ; 
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 scalar_t__ MODE_LOCAL_CHARS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSG_OOB ; 
 int /*<<< orphan*/  NFDBITS ; 
 int /*<<< orphan*/  SIOCATMARK ; 
 int SYNCHing ; 
 int TerminalRead (char*,int) ; 
 TYPE_5__ clocks ; 
 int /*<<< orphan*/  didnetreceive ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int fdsn ; 
 int flushout ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  globalmode ; 
 int howmany (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ibitsp ; 
 int /*<<< orphan*/  ioctl (int,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ isatty (int) ; 
 scalar_t__ malloc (int) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int net ; 
 scalar_t__ netdata ; 
 int netflush () ; 
 TYPE_1__ netiring ; 
 int /*<<< orphan*/ * obitsp ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int read (int,char*,int) ; 
 int recv (int,char*,int,int /*<<< orphan*/ ) ; 
 int ring_empty_consecutive (TYPE_1__*) ; 
 int /*<<< orphan*/  ring_supplied (TYPE_1__*,int) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  settimer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int stilloob (int) ; 
 char* strerror (scalar_t__) ; 
 char termEofChar ; 
 scalar_t__ termdata ; 
 int tin ; 
 int tout ; 
 scalar_t__ ttyflush (int) ; 
 TYPE_1__ ttyiring ; 
 int /*<<< orphan*/ * xbitsp ; 

int
process_rings(int netin, int netout, int netex, int ttyin, int ttyout, int poll)
{
    int c;
    int returnValue = 0;
    static struct timeval TimeValue = { 0, 0 };
    int maxfd = -1;
    int tmp;

    if ((netout || netin || netex) && net > maxfd)
	maxfd = net;
    
    if (ttyout && tout > maxfd)
	maxfd = tout;
    if (ttyin && tin > maxfd)
	maxfd = tin;
    tmp = howmany(maxfd+1, NFDBITS) * sizeof(fd_mask);
    if (tmp > fdsn) {
	if (ibitsp)
	    free(ibitsp);
	if (obitsp)
	    free(obitsp);
	if (xbitsp)
	    free(xbitsp);
	
	fdsn = tmp;
	if ((ibitsp = (fd_set *)malloc(fdsn)) == NULL)
	    err(1, "malloc");
	if ((obitsp = (fd_set *)malloc(fdsn)) == NULL)
	    err(1, "malloc");
	if ((xbitsp = (fd_set *)malloc(fdsn)) == NULL)
	    err(1, "malloc");
	memset(ibitsp, 0, fdsn);
	memset(obitsp, 0, fdsn);
	memset(xbitsp, 0, fdsn);
    }
    
    if (netout)
	FD_SET(net, obitsp);
    if (ttyout)
	FD_SET(tout, obitsp);
    if (ttyin)
	FD_SET(tin, ibitsp);
    if (netin)
	FD_SET(net, ibitsp);
    if (netex)
	FD_SET(net, xbitsp);
    if ((c = select(maxfd + 1, ibitsp, obitsp, xbitsp,
	     (poll == 0)? (struct timeval *)0 : &TimeValue)) < 0) {
	if (c == -1) {
		    /*
		     * we can get EINTR if we are in line mode,
		     * and the user does an escape (TSTP), or
		     * some other signal generator.
		     */
	    if (errno == EINTR) {
		return 0;
	    }
		    /* I don't like this, does it ever happen? */
	    printf("sleep(5) from telnet, after select: %s\r\n", strerror(errno));
	    sleep(5);
	}
	return 0;
    }

    /*
     * Any urgent data?
     */
    if (FD_ISSET(net, xbitsp)) {
	FD_CLR(net, xbitsp);
	SYNCHing = 1;
	(void) ttyflush(1);	/* flush already enqueued data */
    }

    /*
     * Something to read from the network...
     */
    if (FD_ISSET(net, ibitsp)) {
	int canread;

	FD_CLR(net, ibitsp);
	canread = ring_empty_consecutive(&netiring);
#if	!defined(SO_OOBINLINE)
	    /*
	     * In 4.2 (and some early 4.3) systems, the
	     * OOB indication and data handling in the kernel
	     * is such that if two separate TCP Urgent requests
	     * come in, one byte of TCP data will be overlaid.
	     * This is fatal for Telnet, but we try to live
	     * with it.
	     *
	     * In addition, in 4.2 (and...), a special protocol
	     * is needed to pick up the TCP Urgent data in
	     * the correct sequence.
	     *
	     * What we do is:  if we think we are in urgent
	     * mode, we look to see if we are "at the mark".
	     * If we are, we do an OOB receive.  If we run
	     * this twice, we will do the OOB receive twice,
	     * but the second will fail, since the second
	     * time we were "at the mark", but there wasn't
	     * any data there (the kernel doesn't reset
	     * "at the mark" until we do a normal read).
	     * Once we've read the OOB data, we go ahead
	     * and do normal reads.
	     *
	     * There is also another problem, which is that
	     * since the OOB byte we read doesn't put us
	     * out of OOB state, and since that byte is most
	     * likely the TELNET DM (data mark), we would
	     * stay in the TELNET SYNCH (SYNCHing) state.
	     * So, clocks to the rescue.  If we've "just"
	     * received a DM, then we test for the
	     * presence of OOB data when the receive OOB
	     * fails (and AFTER we did the normal mode read
	     * to clear "at the mark").
	     */
	if (SYNCHing) {
	    int atmark;
	    static int bogus_oob = 0, first = 1;

	    ioctl(net, SIOCATMARK, (char *)&atmark);
	    if (atmark) {
		c = recv(net, netiring.supply, canread, MSG_OOB);
		if ((c == -1) && (errno == EINVAL)) {
		    c = recv(net, netiring.supply, canread, 0);
		    if (clocks.didnetreceive < clocks.gotDM) {
			SYNCHing = stilloob(net);
		    }
		} else if (first && c > 0) {
		    /*
		     * Bogosity check.  Systems based on 4.2BSD
		     * do not return an error if you do a second
		     * recv(MSG_OOB).  So, we do one.  If it
		     * succeeds and returns exactly the same
		     * data, then assume that we are running
		     * on a broken system and set the bogus_oob
		     * flag.  (If the data was different, then
		     * we probably got some valid new data, so
		     * increment the count...)
		     */
		    int i;
		    i = recv(net, netiring.supply + c, canread - c, MSG_OOB);
		    if (i == c &&
			memcmp(netiring.supply, netiring.supply + c, i) == 0) {
			bogus_oob = 1;
			first = 0;
		    } else if (i < 0) {
			bogus_oob = 0;
			first = 0;
		    } else
			c += i;
		}
		if (bogus_oob && c > 0) {
		    int i;
		    /*
		     * Bogosity.  We have to do the read
		     * to clear the atmark to get out of
		     * an infinate loop.
		     */
		    i = read(net, netiring.supply + c, canread - c);
		    if (i > 0)
			c += i;
		}
	    } else {
		c = recv(net, netiring.supply, canread, 0);
	    }
	} else {
	    c = recv(net, netiring.supply, canread, 0);
	}
	settimer(didnetreceive);
#else	/* !defined(SO_OOBINLINE) */
	c = recv(net, (char *)netiring.supply, canread, 0);
#endif	/* !defined(SO_OOBINLINE) */
	if (c < 0 && errno == EWOULDBLOCK) {
	    c = 0;
	} else if (c <= 0) {
	    return -1;
	}
	if (netdata) {
	    Dump('<', netiring.supply, c);
	}
	if (c)
	    ring_supplied(&netiring, c);
	returnValue = 1;
    }

    /*
     * Something to read from the tty...
     */
    if (FD_ISSET(tin, ibitsp)) {
	FD_CLR(tin, ibitsp);
	c = TerminalRead(ttyiring.supply, ring_empty_consecutive(&ttyiring));
	if (c < 0 && errno == EIO)
	    c = 0;
	if (c < 0 && errno == EWOULDBLOCK) {
	    c = 0;
	} else {
	    /* EOF detection for line mode!!!! */
	    if ((c == 0) && MODE_LOCAL_CHARS(globalmode) && isatty(tin)) {
			/* must be an EOF... */
		*ttyiring.supply = termEofChar;
		c = 1;
	    }
	    if (c <= 0) {
		return -1;
	    }
	    if (termdata) {
		Dump('<', ttyiring.supply, c);
	    }
	    ring_supplied(&ttyiring, c);
	}
	returnValue = 1;		/* did something useful */
    }

    if (FD_ISSET(net, obitsp)) {
	FD_CLR(net, obitsp);
	returnValue |= netflush();
    }
    if (FD_ISSET(tout, obitsp)) {
	FD_CLR(tout, obitsp);
	returnValue |= (ttyflush(SYNCHing|flushout) > 0);
    }

    return returnValue;
}