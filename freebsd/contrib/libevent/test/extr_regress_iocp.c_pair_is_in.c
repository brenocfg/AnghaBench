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
struct dummy_overlapped {int call_count; uintptr_t* keys; scalar_t__* sizes; int /*<<< orphan*/  lock; } ;
typedef  scalar_t__ ev_ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVLOCK_LOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVLOCK_UNLOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pair_is_in(struct dummy_overlapped *o, uintptr_t key, ev_ssize_t n)
{
	int i;
	int result = 0;
	EVLOCK_LOCK(o->lock, 0);
	for (i=0; i < o->call_count; ++i) {
		if (o->keys[i] == key && o->sizes[i] == n) {
			result = 1;
			break;
		}
	}
	EVLOCK_UNLOCK(o->lock, 0);
	return result;
}