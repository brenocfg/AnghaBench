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
struct rq_wb {int dummy; } ;
struct rq_qos {int dummy; } ;
struct request {int /*<<< orphan*/  wbt_flags; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 struct rq_wb* RQWB (struct rq_qos*) ; 
 int /*<<< orphan*/  bio_to_wbt_flags (struct rq_wb*,struct bio*) ; 

__attribute__((used)) static void wbt_track(struct rq_qos *rqos, struct request *rq, struct bio *bio)
{
	struct rq_wb *rwb = RQWB(rqos);
	rq->wbt_flags |= bio_to_wbt_flags(rwb, bio);
}