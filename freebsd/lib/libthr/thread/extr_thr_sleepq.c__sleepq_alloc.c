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
struct sleepqueue {int /*<<< orphan*/  sq_freeq; int /*<<< orphan*/  sq_blocked; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 struct sleepqueue* calloc (int,int) ; 

struct sleepqueue *
_sleepq_alloc(void)
{
	struct sleepqueue *sq;

	sq = calloc(1, sizeof(struct sleepqueue));
	TAILQ_INIT(&sq->sq_blocked);
	SLIST_INIT(&sq->sq_freeq);
	return (sq);
}