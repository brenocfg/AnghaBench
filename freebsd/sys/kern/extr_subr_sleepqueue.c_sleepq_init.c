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
struct sleepqueue {int /*<<< orphan*/  sq_free; scalar_t__* sq_blockedcnt; int /*<<< orphan*/ * sq_blocked; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int NR_SLEEPQS ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (void*,int) ; 

__attribute__((used)) static int
sleepq_init(void *mem, int size, int flags)
{
	struct sleepqueue *sq;
	int i;

	bzero(mem, size);
	sq = mem;
	for (i = 0; i < NR_SLEEPQS; i++) {
		TAILQ_INIT(&sq->sq_blocked[i]);
		sq->sq_blockedcnt[i] = 0;
	}
	LIST_INIT(&sq->sq_free);
	return (0);
}