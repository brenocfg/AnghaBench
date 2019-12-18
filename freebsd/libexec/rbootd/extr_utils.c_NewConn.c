#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int bootfd; int /*<<< orphan*/ * next; } ;
typedef  TYPE_1__ RMPCONN ;

/* Variables and functions */
 int /*<<< orphan*/  EnetStr (TYPE_1__*) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 TYPE_1__* LastFree ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

RMPCONN *
NewConn(RMPCONN *rconn)
{
	RMPCONN *rtmp;

	if (LastFree == NULL) {		/* nothing cached; make a new one */
		if ((rtmp = (RMPCONN *) malloc(sizeof(RMPCONN))) == NULL) {
			syslog(LOG_ERR, "NewConn: out of memory (%s)",
			       EnetStr(rconn));
			return(NULL);
		}
	} else {			/* use the cached RMPCONN */
		rtmp = LastFree;
		LastFree = NULL;
	}

	/*
	 *  Copy template into `rtmp', init file descriptor to `-1' and
	 *  set ptr to next elem NULL.
	 */
	memmove((char *)rtmp, (char *)rconn, sizeof(RMPCONN));
	rtmp->bootfd = -1;
	rtmp->next = NULL;

	return(rtmp);
}