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
struct mkuz_fifo_queue {int length; int /*<<< orphan*/  mtx; int /*<<< orphan*/ * first; struct mkuz_bchain_link* last; int /*<<< orphan*/  cvar; } ;
struct mkuz_blk {int dummy; } ;
struct mkuz_bchain_link {struct mkuz_blk* this; struct mkuz_bchain_link* prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (struct mkuz_bchain_link*) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

struct mkuz_blk *
mkuz_fqueue_deq(struct mkuz_fifo_queue *fqp)
{
    struct mkuz_bchain_link *ip;
    struct mkuz_blk *bp;

    pthread_mutex_lock(&fqp->mtx);
    while (fqp->last == NULL) {
        pthread_cond_wait(&fqp->cvar, &fqp->mtx);
    }
#if defined(MKUZ_DEBUG)
    assert(fqp->length > 0);
#endif
    ip = fqp->last;
    fqp->last = ip->prev;
    if (fqp->last == NULL) {
#if defined(MKUZ_DEBUG)
        assert(fqp->length == 1);
#endif
        fqp->first = NULL;
    }
    fqp->length -= 1;
    pthread_mutex_unlock(&fqp->mtx);
    bp = ip->this;
    free(ip);

    return bp;
}