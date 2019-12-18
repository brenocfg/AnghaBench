#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint ;
typedef  int /*<<< orphan*/  pdu_t ;
struct TYPE_8__ {int /*<<< orphan*/  tsih; int /*<<< orphan*/  NSG; scalar_t__ T; int /*<<< orphan*/  CSG; int /*<<< orphan*/  status; } ;
typedef  TYPE_1__ login_rsp_t ;
struct TYPE_9__ {int /*<<< orphan*/  tsih; int /*<<< orphan*/  csg; TYPE_3__* op; } ;
typedef  TYPE_2__ isess_t ;
struct TYPE_10__ {int /*<<< orphan*/ * tgtChapDigest; } ;
typedef  TYPE_3__ isc_opt_t ;

/* Variables and functions */
 int CLASS1_ERRS ; 
 int CLASS3_ERRS ; 
 int /*<<< orphan*/  FF_PHASE ; 
 int /*<<< orphan*/  SN_PHASE ; 
 int /*<<< orphan*/  debug (int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 scalar_t__ handleTgtResp (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,char*) ; 
 int /*<<< orphan*/  processParams (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setOptions (TYPE_2__*,int /*<<< orphan*/ ) ; 
 char** status_class1 ; 
 char** status_class3 ; 

__attribute__((used)) static int
handleLoginResp(isess_t *sess, pdu_t *pp)
{
     login_rsp_t *lp = (login_rsp_t *)pp;
     uint	st_class, status = ntohs(lp->status);

     debug_called(3);
     debug(4, "Tbit=%d csg=%d nsg=%d status=%x", lp->T, lp->CSG, lp->NSG, status);

     st_class  = status >> 8;
     if(status) {
	  uint	st_detail = status & 0xff;

	  switch(st_class) {
	  case 1: // Redirect
	       switch(st_detail) {
		    // the ITN (iSCSI target Name) requests a: 
	       case 1: // temporary address change
	       case 2: // permanent address change
		    status = 0;
	       }
	       break;

	  case 2: // Initiator Error
	       if(st_detail < CLASS1_ERRS)
		    printf("0x%04x: %s\n", status, status_class1[st_detail]);
	       break;

	  case 3:
	       if(st_detail < CLASS3_ERRS)
		    printf("0x%04x: %s\n", status, status_class3[st_detail]);
	       break;
	  }
     }
	  
     if(status == 0) {
	  processParams(sess, pp);
	  setOptions(sess, 0); // XXX: just in case ...

	  if(lp->T) {
	       isc_opt_t	*op = sess->op;

	       if(sess->csg == SN_PHASE && (op->tgtChapDigest != NULL))
		    if(handleTgtResp(sess, pp) != 0)
			 return 1; // XXX: Authentication failure ...
	       sess->csg = lp->NSG;
	       if(sess->csg == FF_PHASE) {
		    // XXX: will need this when implementing reconnect.
		    sess->tsih = lp->tsih;
		    debug(2, "TSIH=%x", sess->tsih);
	       }
	  }
     }

     return st_class;
}