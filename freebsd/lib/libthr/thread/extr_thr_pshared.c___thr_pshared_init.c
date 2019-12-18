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

/* Variables and functions */
 int HASH_SIZE ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _thr_urwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pshared_hash ; 
 int /*<<< orphan*/  pshared_lock ; 

void
__thr_pshared_init(void)
{
	int i;

	_thr_urwlock_init(&pshared_lock);
	for (i = 0; i < HASH_SIZE; i++)
		LIST_INIT(&pshared_hash[i]);
}