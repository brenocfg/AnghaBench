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
struct alq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALD_LOCK () ; 
 int /*<<< orphan*/  ALD_UNLOCK () ; 
 int EBUSY ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct alq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ald_queues ; 
 scalar_t__ ald_shutingdown ; 
 int /*<<< orphan*/  aq_link ; 

__attribute__((used)) static int
ald_add(struct alq *alq)
{
	int error;

	error = 0;

	ALD_LOCK();
	if (ald_shutingdown) {
		error = EBUSY;
		goto done;
	}
	LIST_INSERT_HEAD(&ald_queues, alq, aq_link);
done:
	ALD_UNLOCK();
	return (error);
}