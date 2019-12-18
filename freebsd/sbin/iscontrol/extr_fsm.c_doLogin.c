#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  trans_t ;
struct TYPE_6__ {int flags; TYPE_2__* op; int /*<<< orphan*/  csg; scalar_t__ tsih; } ;
typedef  TYPE_1__ isess_t ;
struct TYPE_7__ {int /*<<< orphan*/  sessionType; int /*<<< orphan*/ * tgtChapSecret; int /*<<< orphan*/ * chapSecret; } ;
typedef  TYPE_2__ isc_opt_t ;

/* Variables and functions */
 int /*<<< orphan*/  FF_PHASE ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LON_PHASE ; 
 int SESS_INITIALLOGIN ; 
 int SESS_INITIALLOGIN1 ; 
 int SESS_LOGGEDIN ; 
 int SESS_NEGODONE ; 
 int SESS_REDIRECT ; 
 int /*<<< orphan*/  SN_PHASE ; 
 int /*<<< orphan*/  T5 ; 
 int /*<<< orphan*/  T7 ; 
 int /*<<< orphan*/  debug (int,char*,int,...) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  doDiscovery (TYPE_1__*) ; 
 int loginPhase (TYPE_1__*) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static trans_t
doLogin(isess_t *sess)
{
     isc_opt_t	*op = sess->op;
     int	status, count;

     debug_called(3);

     if(op->chapSecret == NULL && op->tgtChapSecret == NULL)
	  /*
	   | don't need any security negotiation
	   | or in other words: we don't have any secrets to exchange
	   */
	  sess->csg = LON_PHASE;
     else
	  sess->csg = SN_PHASE;

     if(sess->tsih) {
	  sess->tsih = 0;	// XXX: no 'reconnect' yet
	  sess->flags &= ~SESS_NEGODONE; // XXX: KLUDGE
     }
     count = 10; // should be more than enough
     do {
	  debug(3, "count=%d csg=%d", count, sess->csg);
	  status = loginPhase(sess);
	  if(count-- == 0)
	       // just in case we get into a loop
	       status = -1;
     } while(status == 0 && (sess->csg != FF_PHASE));

     sess->flags &= ~SESS_INITIALLOGIN;
     debug(3, "status=%d", status);

     switch(status) {
     case 0: // all is ok ...
	  sess->flags |= SESS_LOGGEDIN;
	  if(strcmp(sess->op->sessionType, "Discovery") == 0)
	       doDiscovery(sess);
	  return T5;

     case 1:	// redirect - temporary/permanent
	  /*
	   | start from scratch?
	   */
	  sess->flags &= ~SESS_NEGODONE;
	  sess->flags |= (SESS_REDIRECT | SESS_INITIALLOGIN1);
	  syslog(LOG_DEBUG, "target sent REDIRECT");
	  return T7;

     case 2: // initiator terminal error
	  return 0;
     case 3: // target terminal error -- could retry ...
	  sleep(5);
	  return T7; // lets try
     default:
	  return 0;
     }
}