#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  bv_hd; } ;
struct TYPE_3__ {int /*<<< orphan*/  bv_hd; } ;
struct bufobj {int bo_domain; TYPE_2__ bo_dirty; TYPE_1__ bo_clean; void* bo_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  BO_LOCKPTR (struct bufobj*) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int atomic_fetchadd_int (int volatile*,int) ; 
 int buf_domains ; 
 int /*<<< orphan*/  rw_init (int /*<<< orphan*/ ,char*) ; 

void
bufobj_init(struct bufobj *bo, void *private)
{
	static volatile int bufobj_cleanq;

        bo->bo_domain =
            atomic_fetchadd_int(&bufobj_cleanq, 1) % buf_domains;
        rw_init(BO_LOCKPTR(bo), "bufobj interlock");
        bo->bo_private = private;
        TAILQ_INIT(&bo->bo_clean.bv_hd);
        TAILQ_INIT(&bo->bo_dirty.bv_hd);
}