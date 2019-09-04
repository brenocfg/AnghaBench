#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
typedef  int /*<<< orphan*/  netadr_t ;
typedef  int /*<<< orphan*/  leakyBucket_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVC_BucketForAddress (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SVC_RateLimit (int /*<<< orphan*/ *,int,int) ; 

qboolean SVC_RateLimitAddress( netadr_t from, int burst, int period ) {
	leakyBucket_t *bucket = SVC_BucketForAddress( from, burst, period );

	return SVC_RateLimit( bucket, burst, period );
}