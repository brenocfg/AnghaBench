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
struct sleepqueue {int sq_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleepq_lock (void*) ; 
 struct sleepqueue* sleepq_lookup (void*) ; 
 int /*<<< orphan*/  sleepq_release (void*) ; 

int
sleepq_type(void *wchan)
{
	struct sleepqueue *sq;
	int type;

	MPASS(wchan != NULL);

	sleepq_lock(wchan);
	sq = sleepq_lookup(wchan);
	if (sq == NULL) {
		sleepq_release(wchan);
		return (-1);
	}
	type = sq->sq_type;
	sleepq_release(wchan);
	return (type);
}