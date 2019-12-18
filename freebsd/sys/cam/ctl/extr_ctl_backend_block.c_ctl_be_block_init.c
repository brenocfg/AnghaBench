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
struct ctl_be_block_softc {int /*<<< orphan*/  lun_list; int /*<<< orphan*/  beio_zone; int /*<<< orphan*/  lock; } ;
struct ctl_be_block_io {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UMA_ALIGN_PTR ; 
 struct ctl_be_block_softc backend_block_softc ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zcreate (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ctl_be_block_init(void)
{
	struct ctl_be_block_softc *softc = &backend_block_softc;

	mtx_init(&softc->lock, "ctlblock", NULL, MTX_DEF);
	softc->beio_zone = uma_zcreate("beio", sizeof(struct ctl_be_block_io),
	    NULL, NULL, NULL, NULL, UMA_ALIGN_PTR, 0);
	STAILQ_INIT(&softc->lun_list);
	return (0);
}