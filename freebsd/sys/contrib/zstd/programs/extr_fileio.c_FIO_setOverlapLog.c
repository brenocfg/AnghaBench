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
struct TYPE_3__ {scalar_t__ nbWorkers; int overlapLog; } ;
typedef  TYPE_1__ FIO_prefs_t ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAYLEVEL (int,char*) ; 

void FIO_setOverlapLog(FIO_prefs_t* const prefs, int overlapLog){
    if (overlapLog && prefs->nbWorkers==0)
        DISPLAYLEVEL(2, "Setting overlapLog is useless in single-thread mode \n");
    prefs->overlapLog = overlapLog;
}