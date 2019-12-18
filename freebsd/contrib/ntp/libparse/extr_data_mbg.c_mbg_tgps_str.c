#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int wn; scalar_t__ tick; scalar_t__ sec; } ;
typedef  TYPE_1__ T_GPS ;

/* Variables and functions */
 long SECSPERDAY ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,long,long,long) ; 
 int /*<<< orphan*/  strlen (char*) ; 

void
mbg_tgps_str(
	char **buffpp,
	T_GPS *tgpsp,
	int size
	)
{
	snprintf(*buffpp, size, "week %d + %ld days + %ld.%07ld sec",
		 tgpsp->wn, (long) tgpsp->sec / SECSPERDAY,
		 (long) tgpsp->sec % SECSPERDAY, (long) tgpsp->tick);
	*buffpp += strlen(*buffpp);
}