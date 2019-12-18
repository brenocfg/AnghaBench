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
struct futex {scalar_t__ refcount; int /*<<< orphan*/  chain; int /*<<< orphan*/  cond; } ;

/* Variables and functions */
 int /*<<< orphan*/  cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct futex*) ; 
 int /*<<< orphan*/  futex_lock ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void futex_put(struct futex *futex) {
    if (--futex->refcount == 0) {
        cond_destroy(&futex->cond);
        list_remove(&futex->chain);
        free(futex);
    }
    unlock(&futex_lock);
}