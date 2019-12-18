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
struct TYPE_3__ {int /*<<< orphan*/  si_note; } ;
struct TYPE_4__ {int /*<<< orphan*/  mtx; TYPE_1__ sel; int /*<<< orphan*/  devq; int /*<<< orphan*/  cv; } ;

/* Variables and functions */
 int /*<<< orphan*/  GID_WHEEL ; 
 int /*<<< orphan*/  MAKEDEV_ETERNAL ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  cv_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_cdevsw ; 
 int /*<<< orphan*/  devctl2_init () ; 
 int /*<<< orphan*/  devctl_dev ; 
 TYPE_2__ devsoftc ; 
 int /*<<< orphan*/  knlist_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  make_dev_credf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
devinit(void)
{
	devctl_dev = make_dev_credf(MAKEDEV_ETERNAL, &dev_cdevsw, 0, NULL,
	    UID_ROOT, GID_WHEEL, 0600, "devctl");
	mtx_init(&devsoftc.mtx, "dev mtx", "devd", MTX_DEF);
	cv_init(&devsoftc.cv, "dev cv");
	TAILQ_INIT(&devsoftc.devq);
	knlist_init_mtx(&devsoftc.sel.si_note, &devsoftc.mtx);
	devctl2_init();
}