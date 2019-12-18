#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int bootfd; } ;
typedef  TYPE_1__ RMPCONN ;

/* Variables and functions */
 TYPE_1__* LastFree ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (char*) ; 

void
FreeConn(RMPCONN *rtmp)
{
	/*
	 *  If the file descriptor is in use, close the file.
	 */
	if (rtmp->bootfd >= 0) {
		(void) close(rtmp->bootfd);
		rtmp->bootfd = -1;
	}

	if (LastFree == NULL)		/* cache for next time */
		rtmp = LastFree;
	else				/* already one cached; free this one */
		free((char *)rtmp);
}