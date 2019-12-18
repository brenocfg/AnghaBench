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
struct cryptop {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_Q_LOCK () ; 
 int /*<<< orphan*/  CRYPTO_Q_UNLOCK () ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct cryptop*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crp_next ; 
 int /*<<< orphan*/  crp_q ; 
 scalar_t__ crp_sleep ; 
 int /*<<< orphan*/  wakeup_one (int /*<<< orphan*/ *) ; 

void
crypto_batch_enqueue(struct cryptop *crp)
{

	CRYPTO_Q_LOCK();
	TAILQ_INSERT_TAIL(&crp_q, crp, crp_next);
	if (crp_sleep)
		wakeup_one(&crp_q);
	CRYPTO_Q_UNLOCK();
}