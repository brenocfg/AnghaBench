#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  bhs; } ;
struct TYPE_13__ {TYPE_1__ ipdu; } ;
typedef  TYPE_2__ pdu_t ;
struct TYPE_14__ {int cmd; int CSG; int NSG; int T; int /*<<< orphan*/  CID; int /*<<< orphan*/  tsih; int /*<<< orphan*/  isid; } ;
typedef  TYPE_3__ login_req_t ;
struct TYPE_15__ {int csg; int flags; int /*<<< orphan*/  tsih; int /*<<< orphan*/  isid; TYPE_5__* op; } ;
typedef  TYPE_4__ isess_t ;
struct TYPE_16__ {char* sessionType; char* initiatorName; char* targetName; char* authMethod; char* maxBurstLength; char* headerDigest; char* dataDigest; char* maxRecvDataSegmentLength; char* errorRecoveryLevel; char* defaultTime2Wait; char* defaultTime2Retain; char* maxOutstandingR2T; char* maxConnections; char* firstBurstLength; int /*<<< orphan*/  immediateData; int /*<<< orphan*/  initialR2T; int /*<<< orphan*/  dataSequenceInOrder; int /*<<< orphan*/  dataPDUInOrder; } ;
typedef  TYPE_5__ isc_opt_t ;

/* Variables and functions */
 int FF_PHASE ; 
 int ISCSI_LOGIN_CMD ; 
#define  LON_PHASE 129 
 int SESS_INITIALLOGIN1 ; 
 int SESS_NEGODONE ; 
#define  SN_PHASE 128 
 int /*<<< orphan*/  addText (TYPE_2__*,char*,char*) ; 
 int authenticate (TYPE_4__*) ; 
 int /*<<< orphan*/  bzero (TYPE_2__*,int) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  handleLoginResp ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int sendPDU (TYPE_4__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 

int
loginPhase(isess_t *sess)
{
     pdu_t		spp, *sp = &spp;
     isc_opt_t  	*op = sess->op;
     login_req_t	*lp;
     int		status = 1;

     debug_called(3);

     bzero(sp, sizeof(pdu_t));
     lp = (login_req_t *)&spp.ipdu.bhs;
     lp->cmd = ISCSI_LOGIN_CMD | 0x40; // login request + Inmediate
     memcpy(lp->isid, sess->isid, 6);
     lp->tsih = sess->tsih;	// MUST be zero the first time!
     lp->CID = htons(1);	// sess->cid?

     if((lp->CSG = sess->csg) == LON_PHASE)
	  lp->NSG = FF_PHASE;	// lets try and go full feature ...
     else
	  lp->NSG = LON_PHASE;
     lp->T = 1;			// transit to next login stage

     if(sess->flags & SESS_INITIALLOGIN1) {
	  sess->flags &= ~SESS_INITIALLOGIN1;

	  addText(sp, "SessionType=%s", op->sessionType);
	  addText(sp, "InitiatorName=%s", op->initiatorName);
	  if(strcmp(op->sessionType, "Discovery") != 0) {
	       addText(sp, "TargetName=%s", op->targetName);
	  }
     }
     switch(sess->csg) {
     case SN_PHASE:	// Security Negotiation
	  addText(sp, "AuthMethod=%s", op->authMethod);
	  break;
	       
     case LON_PHASE:	// Login Operational Negotiation
	  if((sess->flags & SESS_NEGODONE) == 0) {
	       sess->flags |= SESS_NEGODONE;
	       addText(sp, "MaxBurstLength=%d", op->maxBurstLength);
	       addText(sp, "HeaderDigest=%s", op->headerDigest);
	       addText(sp, "DataDigest=%s", op->dataDigest);
	       addText(sp, "MaxRecvDataSegmentLength=%d", op->maxRecvDataSegmentLength);
	       addText(sp, "ErrorRecoveryLevel=%d", op->errorRecoveryLevel);
	       addText(sp, "DefaultTime2Wait=%d", op->defaultTime2Wait);
	       addText(sp, "DefaultTime2Retain=%d", op->defaultTime2Retain);
	       addText(sp, "DataPDUInOrder=%s", op->dataPDUInOrder? "Yes": "No");
	       addText(sp, "DataSequenceInOrder=%s", op->dataSequenceInOrder? "Yes": "No");
	       addText(sp, "MaxOutstandingR2T=%d", op->maxOutstandingR2T);

	       if(strcmp(op->sessionType, "Discovery") != 0) {
		    addText(sp, "MaxConnections=%d", op->maxConnections);
		    addText(sp, "FirstBurstLength=%d", op->firstBurstLength);
		    addText(sp, "InitialR2T=%s", op->initialR2T? "Yes": "No");
		    addText(sp, "ImmediateData=%s", op->immediateData? "Yes": "No");
	       }
	  }

	  break;
     }

     status = sendPDU(sess, &spp, handleLoginResp);

     switch(status) {
     case 0: // all is ok ...
	  if(sess->csg == SN_PHASE)
	       /*
		| if we are still here, then we need
		| to exchange some secrets ...
	        */
	       status = authenticate(sess);
     }

     return status;
}