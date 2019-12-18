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
typedef  scalar_t__ time_t ;
struct TYPE_8__ {int /*<<< orphan*/  r_type; } ;
struct TYPE_7__ {scalar_t__ tv_sec; } ;
struct TYPE_9__ {TYPE_2__ rmp; TYPE_1__ tstamp; struct TYPE_9__* next; } ;
typedef  TYPE_3__ RMPCONN ;

/* Variables and functions */
 int /*<<< orphan*/  EnetStr (TYPE_3__*) ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 scalar_t__ RMP_TIMEOUT ; 
 int /*<<< orphan*/  RemoveConn (TYPE_3__*) ; 
 TYPE_3__* RmpConns ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

void
DoTimeout(void)
{
	RMPCONN *rtmp;
	time_t now;

	/*
	 *  For each active connection, if RMP_TIMEOUT seconds have passed
	 *  since the last packet was sent, delete the connection.
	 */
	now = time(NULL);
	for (rtmp = RmpConns; rtmp != NULL; rtmp = rtmp->next)
		if ((rtmp->tstamp.tv_sec + RMP_TIMEOUT) < now) {
			syslog(LOG_WARNING, "%s: connection timed out (%u)",
			       EnetStr(rtmp), rtmp->rmp.r_type);
			RemoveConn(rtmp);
		}
}