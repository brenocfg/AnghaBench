#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  val ;
typedef  int /*<<< orphan*/  trans_t ;
typedef  int /*<<< orphan*/  timeout ;
typedef  int time_t ;
typedef  int timeval ;
struct addrinfo {int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; struct addrinfo* ai_next; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  pbuf ;
struct TYPE_5__ {char* address; int port; int /*<<< orphan*/  pgt; } ;
struct TYPE_6__ {int flags; int soc; int reconnect_time; int reconnect_cnt1; TYPE_1__ target; TYPE_3__* op; int /*<<< orphan*/  reconnect_cnt; int /*<<< orphan*/  redirect_cnt; } ;
typedef  TYPE_2__ isess_t ;
struct TYPE_7__ {int port; char* targetAddress; int sockbufsize; int /*<<< orphan*/  targetPortalGroupTag; } ;
typedef  TYPE_3__ isc_opt_t ;
typedef  int /*<<< orphan*/  hints ;

/* Variables and functions */
#define  ECONNREFUSED 131 
#define  EHOSTUNREACH 130 
#define  ENETUNREACH 129 
#define  ETIMEDOUT 128 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  LOG_CRIT ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  PF_UNSPEC ; 
 int SESS_CONNECTED ; 
 int SESS_RECONNECT ; 
 int SESS_REDIRECT ; 
 int /*<<< orphan*/  SHUT_RDWR ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_RCVBUF ; 
 int /*<<< orphan*/  SO_RCVTIMEO ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 int /*<<< orphan*/  SO_SNDBUF ; 
 int /*<<< orphan*/  SO_SNDTIMEO ; 
 int /*<<< orphan*/  T1 ; 
 int /*<<< orphan*/  TCP_KEEPALIVE ; 
 int /*<<< orphan*/  TCP_NODELAY ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connect (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug (int,char*,char*,...) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 char* gai_strerror (int) ; 
 int getaddrinfo (char*,char*,struct addrinfo*,struct addrinfo**) ; 
 scalar_t__ getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  shutdown (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strerror (int) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,...) ; 
 int time (int /*<<< orphan*/ ) ; 

__attribute__((used)) static trans_t
tcpConnect(isess_t *sess)
{
     isc_opt_t *op = sess->op;
     int	val, sv_errno, soc;
     struct     addrinfo *res, *res0, hints;
     char	pbuf[10];

     debug_called(3);
     if(sess->flags & (SESS_RECONNECT|SESS_REDIRECT)) {
	  syslog(LOG_INFO, "%s", (sess->flags & SESS_RECONNECT)
		 ? "Reconnect": "Redirected");
	  
	  debug(1, "%s", (sess->flags & SESS_RECONNECT) ? "Reconnect": "Redirected");
	  shutdown(sess->soc, SHUT_RDWR);
	  //close(sess->soc);
	  sess->soc = -1;

	  sess->flags &= ~SESS_CONNECTED;
	  if(sess->flags & SESS_REDIRECT) {
	       sess->redirect_cnt++;
	       sess->flags |= SESS_RECONNECT;
	  } else
	       sleep(2); // XXX: actually should be ?
#ifdef notyet
	  {
	       time_t	sec;
	       // make sure we are not in a loop
	       // XXX: this code has to be tested
	       sec = time(0) - sess->reconnect_time;
	       if(sec > (5*60)) {
		    // if we've been connected for more that 5 minutes
		    // then just reconnect
		    sess->reconnect_time = sec;
		    sess->reconnect_cnt1 = 0;
	       }
	       else {
		    //
		    sess->reconnect_cnt1++;
		    if((sec / sess->reconnect_cnt1) < 2) {
			 // if less that 2 seconds from the last reconnect
			 // we are most probably looping
			 syslog(LOG_CRIT, "too many reconnects %d", sess->reconnect_cnt1);
			 return 0;
		    }
	       }
	  }
#endif
	  sess->reconnect_cnt++;
     }

     snprintf(pbuf, sizeof(pbuf), "%d", op->port);
     memset(&hints, 0, sizeof(hints));
     hints.ai_family	= PF_UNSPEC;
     hints.ai_socktype	= SOCK_STREAM;
     debug(1, "targetAddress=%s port=%d", op->targetAddress, op->port);
     if((val = getaddrinfo(op->targetAddress, pbuf, &hints, &res0)) != 0) {
          fprintf(stderr, "getaddrinfo(%s): %s\n", op->targetAddress, gai_strerror(val));
          return 0;
     }
     sess->flags &= ~SESS_CONNECTED;
     sv_errno = 0;
     soc = -1;
     for(res = res0; res; res = res->ai_next) {
	  soc = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	  if (soc == -1)
	       continue;

	  // from Patrick.Guelat@imp.ch:
	  // iscontrol can be called without waiting for the socket entry to time out
	  val = 1;
	  if(setsockopt(soc, SOL_SOCKET, SO_REUSEADDR, &val, (socklen_t)sizeof(val)) < 0) {
	       fprintf(stderr, "Cannot set socket SO_REUSEADDR %d: %s\n\n",
		       errno, strerror(errno));
	  }

	  if(connect(soc, res->ai_addr, res->ai_addrlen) == 0)
	       break;
	  sv_errno = errno;
	  close(soc);
	  soc = -1;
     }
     freeaddrinfo(res0);
     if(soc != -1) {
	  sess->soc = soc;

#if 0
	  struct	timeval timeout;

	  val = 1;
	  if(setsockopt(sess->soc, IPPROTO_TCP, TCP_KEEPALIVE, &val, sizeof(val)) < 0)
	       fprintf(stderr, "Cannot set socket KEEPALIVE option err=%d %s\n",
		       errno, strerror(errno));

	  if(setsockopt(sess->soc, IPPROTO_TCP, TCP_NODELAY, &val, sizeof(val)) < 0)
	       fprintf(stderr, "Cannot set socket NO delay option err=%d %s\n",
		       errno, strerror(errno));
	  
	  timeout.tv_sec = 10;
	  timeout.tv_usec = 0;
	  if((setsockopt(sess->soc, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout)) < 0)
	     || (setsockopt(sess->soc, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0)) {
	       fprintf(stderr, "Cannot set socket timeout to %ld err=%d %s\n",
		       timeout.tv_sec, errno, strerror(errno));
	  }
#endif
#ifdef CURIOUS
	  { 
	       int len = sizeof(val);
	       if(getsockopt(sess->soc, SOL_SOCKET, SO_SNDBUF, &val, &len) == 0)
		    fprintf(stderr, "was: SO_SNDBUF=%dK\n", val/1024);
	  }
#endif
	  if(sess->op->sockbufsize) {
	       val = sess->op->sockbufsize * 1024;
	       if((setsockopt(sess->soc, SOL_SOCKET, SO_SNDBUF, &val, sizeof(val)) < 0)
		  || (setsockopt(sess->soc, SOL_SOCKET, SO_RCVBUF, &val, sizeof(val)) < 0)) {
		    fprintf(stderr, "Cannot set socket sndbuf & rcvbuf to %d err=%d %s\n",
			    val, errno, strerror(errno));
		    return 0; 
	       }
	  }
	  sess->flags |= SESS_CONNECTED;
	  return T1;
     }

     fprintf(stderr, "errno=%d\n", sv_errno);
     perror("connect");
     switch(sv_errno) {
     case ECONNREFUSED:
     case EHOSTUNREACH:
     case ENETUNREACH:
     case ETIMEDOUT:
	  if((sess->flags & SESS_REDIRECT) == 0) {
	       if(strcmp(op->targetAddress, sess->target.address) != 0) {
		    syslog(LOG_INFO, "reconnecting to original target address");
		    free(op->targetAddress);
		    op->targetAddress           = sess->target.address;
		    op->port                    = sess->target.port;
		    op->targetPortalGroupTag    = sess->target.pgt;
		    return T1;
	       }
	  }
	  sleep(5); // for now ...
	  return T1;
     default:
	  return 0; // terminal error
     }
}