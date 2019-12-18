#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int state_t ;
struct TYPE_12__ {int /*<<< orphan*/  pgt; int /*<<< orphan*/  port; int /*<<< orphan*/  address; } ;
struct TYPE_13__ {int fd; int soc; int flags; TYPE_1__ target; TYPE_3__* op; } ;
typedef  TYPE_2__ isess_t ;
struct TYPE_14__ {int /*<<< orphan*/  targetPortalGroupTag; int /*<<< orphan*/  port; int /*<<< orphan*/  targetAddress; } ;
typedef  TYPE_3__ isc_opt_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_INFO ; 
#define  S1 149 
#define  S2 148 
#define  S4 147 
#define  S5 146 
#define  S6 145 
#define  S7 144 
#define  S8 143 
 int SESS_INITIALLOGIN ; 
 int SESS_INITIALLOGIN1 ; 
#define  T1 142 
#define  T10 141 
#define  T11 140 
#define  T12 139 
#define  T13 138 
#define  T14 137 
#define  T15 136 
#define  T16 135 
#define  T18 134 
#define  T2 133 
#define  T4 132 
#define  T5 131 
#define  T7 130 
#define  T8 129 
#define  T9 128 
 TYPE_2__* calloc (int,int) ; 
 int /*<<< orphan*/  doLogin (TYPE_2__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  inLogout (TYPE_2__*) ; 
 int /*<<< orphan*/  startLogout (TYPE_2__*) ; 
 int /*<<< orphan*/  startSession (TYPE_2__*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  supervise (TYPE_2__*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tcpConnect (TYPE_2__*) ; 

int
fsm(isc_opt_t *op)
{
     state_t	state;
     isess_t	*sess;

     if((sess = calloc(1, sizeof(isess_t))) == NULL) {
	  // boy, is this a bad start ...
	  fprintf(stderr, "no memory!\n");
	  return -1;
     }

     state = S1;
     sess->op = op;
     sess->fd = -1;
     sess->soc = -1;
     sess->target.address = strdup(op->targetAddress);
     sess->target.port = op->port;
     sess->target.pgt = op->targetPortalGroupTag;

     sess->flags = SESS_INITIALLOGIN | SESS_INITIALLOGIN1;

     do {
	  switch(state) {

	  case S1:
	       switch(tcpConnect(sess)) {
	       case T1: state = S2; break;
	       default: state = S8; break;
	       }
	       break;

	  case S2:
	       switch(startSession(sess)) {
	       case T2: state = S1; break;
	       case T4: state = S4; break;
	       default: state = S8; break;
	       }
	       break;

	  case S4:
	       switch(doLogin(sess)) {
	       case T7:  state = S1; break;
	       case T5:  state = S5; break;
	       default: state = S8; break;
	       }
	       break;

	  case S5:
	       switch(supervise(sess)) {
	       case T8:  state = S1; break;
	       case T9:  state = S6; break;
	       case T11: state = S7; break;
	       case T15: state = S8; break;
	       default: state = S8; break;
	       }
	       break;

	  case S6:
	       switch(startLogout(sess)) {
	       case T13: state = S1; break;
	       case T14: state = S6; break;
	       case T16: state = S8; break;
	       default: state = S8; break;
	       }
	       break;
	  
	  case S7: 
	       switch(inLogout(sess)) {
	       case T18: state = S1; break;
	       case T10: state = S6; break;
	       case T12: state = S7; break;
	       case T16: state = S8; break;
	       default: state = S8; break;
	       }
	       break;

	  case S8:
	       // maybe do some clean up?
	       syslog(LOG_INFO, "terminated");
	       return 0;
	  }
     } while(1);
}