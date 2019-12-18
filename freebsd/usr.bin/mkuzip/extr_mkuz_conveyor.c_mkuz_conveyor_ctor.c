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
struct mkuz_conveyor {int /*<<< orphan*/ * wthreads; void* results; void* wrk_queue; } ;
struct mkuz_cfg {int nworkers; } ;
struct cw_args {struct mkuz_conveyor* cvp; struct mkuz_cfg* cfp; } ;
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 int /*<<< orphan*/  cworker ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 void* mkuz_fqueue_ctor (int) ; 
 void* mkuz_safe_zmalloc (int) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 

struct mkuz_conveyor *
mkuz_conveyor_ctor(struct mkuz_cfg *cfp)
{
    struct mkuz_conveyor *cp;
    struct cw_args *cwp;
    int i, r;

    cp = mkuz_safe_zmalloc(sizeof(struct mkuz_conveyor) +
      (sizeof(pthread_t) * cfp->nworkers));

    cp->wrk_queue = mkuz_fqueue_ctor(1);
    cp->results = mkuz_fqueue_ctor(1);

    for (i = 0; i < cfp->nworkers; i++) {
        cwp = mkuz_safe_zmalloc(sizeof(struct cw_args));
        cwp->cfp = cfp;
        cwp->cvp = cp;
        r = pthread_create(&cp->wthreads[i], NULL, cworker, (void *)cwp);
        if (r != 0) {
            errx(1, "mkuz_conveyor_ctor: pthread_create() failed");
            /* Not reached */
        }
    }
    return (cp);
}