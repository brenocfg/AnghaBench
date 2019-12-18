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
struct bio {int dummy; } ;
typedef  enum wbt_flags { ____Placeholder_wbt_flags } wbt_flags ;

/* Variables and functions */
 struct rq_wb* RQWB (struct rq_qos*) ; 
 int /*<<< orphan*/  __wbt_done (struct rq_qos*,int) ; 
 int bio_to_wbt_flags (struct rq_wb*,struct bio*) ; 

__attribute__((used)) static void wbt_cleanup(struct rq_qos *rqos, struct bio *bio)
{
	struct rq_wb *rwb = RQWB(rqos);
	enum wbt_flags flags = bio_to_wbt_flags(rwb, bio);
	__wbt_done(rqos, flags);
}