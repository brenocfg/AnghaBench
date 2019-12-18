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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct slabhash_testkey {TYPE_1__ entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct slabhash_testkey*) ; 
 int /*<<< orphan*/  lock_rw_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void delkey(struct slabhash_testkey* k) {
	lock_rw_destroy(&k->entry.lock); free(k);}