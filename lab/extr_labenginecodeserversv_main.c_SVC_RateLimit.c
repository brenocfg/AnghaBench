#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_4__ {int lastTime; int burst; } ;
typedef  TYPE_1__ leakyBucket_t ;
struct TYPE_5__ {scalar_t__ integer; } ;

/* Variables and functions */
 int Sys_Milliseconds () ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_2__* sv_rateLimit ; 

qboolean SVC_RateLimit( leakyBucket_t *bucket, int burst, int period ) {
	if ( bucket != NULL ) {
		if (sv_rateLimit->integer){
			int now = Sys_Milliseconds();
			int interval = now - bucket->lastTime;
			int expired = interval / period;
			int expiredRemainder = interval % period;

			if ( expired > bucket->burst || interval < 0 ) {
				bucket->burst = 0;
				bucket->lastTime = now;
			} else {
				bucket->burst -= expired;
				bucket->lastTime = now - expiredRemainder;
			}

			if ( bucket->burst < burst ) {
				bucket->burst++;
				return qfalse;
			}
		} else {
			return qfalse;
		}
	}

	return qtrue;
}