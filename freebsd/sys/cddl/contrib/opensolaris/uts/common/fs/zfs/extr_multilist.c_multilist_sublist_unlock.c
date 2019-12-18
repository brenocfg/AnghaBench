#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  mls_lock; } ;
typedef  TYPE_1__ multilist_sublist_t ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

void
multilist_sublist_unlock(multilist_sublist_t *mls)
{
	mutex_exit(&mls->mls_lock);
}