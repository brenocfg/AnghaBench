#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  sc_lock; int /*<<< orphan*/  sc_queues; } ;

/* Variables and functions */
 int HASHSIZE ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _thr_umutex_init (int /*<<< orphan*/ *) ; 
 TYPE_1__* sc_table ; 

void
_sleepq_init(void)
{
	int	i;

	for (i = 0; i < HASHSIZE; ++i) {
		LIST_INIT(&sc_table[i].sc_queues);
		_thr_umutex_init(&sc_table[i].sc_lock);
	}
}