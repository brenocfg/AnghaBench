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
struct sighand {int refcount; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  lock_init (int /*<<< orphan*/ *) ; 
 struct sighand* malloc (int) ; 
 int /*<<< orphan*/  memset (struct sighand*,int /*<<< orphan*/ ,int) ; 

struct sighand *sighand_new() {
    struct sighand *sighand = malloc(sizeof(struct sighand));
    if (sighand == NULL)
        return NULL;
    memset(sighand, 0, sizeof(struct sighand));
    sighand->refcount = 1;
    lock_init(&sighand->lock);
    return sighand;
}