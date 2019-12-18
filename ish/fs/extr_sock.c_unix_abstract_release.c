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
struct unix_abstract {scalar_t__ refcount; int /*<<< orphan*/  links; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct unix_abstract*) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unix_abstract_lock ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void unix_abstract_release(struct unix_abstract *name) {
    lock(&unix_abstract_lock);
    if (--name->refcount == 0) {
        list_remove(&name->links);
        free(name);
    }
    unlock(&unix_abstract_lock);
}