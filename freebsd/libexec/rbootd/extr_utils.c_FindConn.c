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
struct TYPE_7__ {int /*<<< orphan*/ * saddr; } ;
struct TYPE_8__ {TYPE_1__ hp_hdr; } ;
struct TYPE_9__ {TYPE_2__ rmp; struct TYPE_9__* next; } ;
typedef  TYPE_3__ RMPCONN ;

/* Variables and functions */
 int /*<<< orphan*/  RMP_ADDRLEN ; 
 TYPE_3__* RmpConns ; 
 scalar_t__ bcmp (char*,char*,int /*<<< orphan*/ ) ; 

RMPCONN *
FindConn(RMPCONN *rconn)
{
	RMPCONN *rtmp;

	for (rtmp = RmpConns; rtmp != NULL; rtmp = rtmp->next)
		if (bcmp((char *)&rconn->rmp.hp_hdr.saddr[0],
		         (char *)&rtmp->rmp.hp_hdr.saddr[0], RMP_ADDRLEN) == 0)
			break;

	return(rtmp);
}