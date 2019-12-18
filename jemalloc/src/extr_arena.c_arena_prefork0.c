#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
struct TYPE_6__ {int /*<<< orphan*/  mtx; } ;
struct TYPE_5__ {int /*<<< orphan*/  mtx; } ;
struct TYPE_7__ {TYPE_2__ decay_muzzy; TYPE_1__ decay_dirty; } ;
typedef  TYPE_3__ arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  malloc_mutex_prefork (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
arena_prefork0(tsdn_t *tsdn, arena_t *arena) {
	malloc_mutex_prefork(tsdn, &arena->decay_dirty.mtx);
	malloc_mutex_prefork(tsdn, &arena->decay_muzzy.mtx);
}