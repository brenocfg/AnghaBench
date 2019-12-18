#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int F; int ttt; int /*<<< orphan*/  cmd; } ;
typedef  TYPE_2__ text_req_t ;
struct TYPE_7__ {int /*<<< orphan*/  bhs; } ;
struct TYPE_9__ {TYPE_1__ ipdu; } ;
typedef  TYPE_3__ pdu_t ;
typedef  int /*<<< orphan*/  isess_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_TEXT_CMD ; 
 int /*<<< orphan*/  addText (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  bzero (TYPE_3__*,int) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  handledDiscoveryResp ; 
 int sendPDU (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
doDiscovery(isess_t *sess)
{
     pdu_t	spp;
     text_req_t	*tp = (text_req_t *)&spp.ipdu.bhs;

     debug_called(3);

     bzero(&spp, sizeof(pdu_t));
     tp->cmd = ISCSI_TEXT_CMD /*| 0x40 */; // because of a bug in openiscsi-target
     tp->F = 1;
     tp->ttt = 0xffffffff;
     addText(&spp, "SendTargets=All");
     return sendPDU(sess, &spp, handledDiscoveryResp);
}