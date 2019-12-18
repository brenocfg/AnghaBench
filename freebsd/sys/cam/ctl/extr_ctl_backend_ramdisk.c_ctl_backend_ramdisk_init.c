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
struct ctl_be_ramdisk_softc {int /*<<< orphan*/  lun_list; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct ctl_be_ramdisk_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ctl_be_ramdisk_softc rd_softc ; 

__attribute__((used)) static int
ctl_backend_ramdisk_init(void)
{
	struct ctl_be_ramdisk_softc *softc = &rd_softc;

	memset(softc, 0, sizeof(*softc));
	mtx_init(&softc->lock, "ctlramdisk", NULL, MTX_DEF);
	STAILQ_INIT(&softc->lun_list);
	return (0);
}