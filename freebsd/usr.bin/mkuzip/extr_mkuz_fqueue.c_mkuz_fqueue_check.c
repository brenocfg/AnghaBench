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
struct mkuz_fifo_queue {struct mkuz_bchain_link* last; } ;
struct mkuz_bchain_link {int /*<<< orphan*/  this; struct mkuz_bchain_link* prev; } ;
typedef  scalar_t__ (* cmp_cb_t ) (int /*<<< orphan*/ ,void*) ;

/* Variables and functions */

__attribute__((used)) static int
mkuz_fqueue_check(struct mkuz_fifo_queue *fqp, cmp_cb_t cmp_cb, void *cap)
{
    struct mkuz_bchain_link *ip;

    for (ip = fqp->last; ip != NULL; ip = ip->prev) {
        if (cmp_cb(ip->this, cap)) {
            return (1);
        }
    }
    return (0);
}