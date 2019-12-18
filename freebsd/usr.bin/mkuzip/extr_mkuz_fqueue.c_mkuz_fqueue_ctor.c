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
struct mkuz_fifo_queue {int wakeup_len; int /*<<< orphan*/  cvar; int /*<<< orphan*/  mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*) ; 
 struct mkuz_fifo_queue* mkuz_safe_zmalloc (int) ; 
 scalar_t__ pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

struct mkuz_fifo_queue *
mkuz_fqueue_ctor(int wakeup_len)
{
    struct mkuz_fifo_queue *fqp;

    fqp = mkuz_safe_zmalloc(sizeof(struct mkuz_fifo_queue));
    fqp->wakeup_len = wakeup_len;
    if (pthread_mutex_init(&fqp->mtx, NULL) != 0) {
        errx(1, "pthread_mutex_init() failed");
    }
    if (pthread_cond_init(&fqp->cvar, NULL) != 0) {
        errx(1, "pthread_cond_init() failed");
    }
    return (fqp);
}