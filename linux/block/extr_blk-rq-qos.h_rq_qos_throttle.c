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
struct request_queue {scalar_t__ rq_qos; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_TRACKED ; 
 int /*<<< orphan*/  __rq_qos_throttle (scalar_t__,struct bio*) ; 
 int /*<<< orphan*/  bio_set_flag (struct bio*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void rq_qos_throttle(struct request_queue *q, struct bio *bio)
{
	/*
	 * BIO_TRACKED lets controllers know that a bio went through the
	 * normal rq_qos path.
	 */
	bio_set_flag(bio, BIO_TRACKED);
	if (q->rq_qos)
		__rq_qos_throttle(q->rq_qos, bio);
}