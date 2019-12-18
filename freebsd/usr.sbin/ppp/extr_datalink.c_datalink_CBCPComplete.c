#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct datalink {TYPE_3__* physical; } ;
struct TYPE_4__ {int /*<<< orphan*/  fsm; } ;
struct TYPE_5__ {TYPE_1__ lcp; } ;
struct TYPE_6__ {TYPE_2__ link; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATALINK_LCP ; 
 int /*<<< orphan*/  datalink_AuthReInit (struct datalink*) ; 
 int /*<<< orphan*/  datalink_NewState (struct datalink*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsm_Close (int /*<<< orphan*/ *) ; 

void
datalink_CBCPComplete(struct datalink *dl)
{
  datalink_NewState(dl, DATALINK_LCP);
  datalink_AuthReInit(dl);
  fsm_Close(&dl->physical->link.lcp.fsm);
}