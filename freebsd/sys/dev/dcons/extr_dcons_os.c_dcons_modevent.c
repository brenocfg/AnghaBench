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
typedef  int /*<<< orphan*/  module_t ;
struct TYPE_4__ {int /*<<< orphan*/  magic; } ;
struct TYPE_3__ {TYPE_2__* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCONS_BUF_SIZE ; 
 int /*<<< orphan*/  DCONS_CON ; 
 int /*<<< orphan*/  DCONS_GDB ; 
 int EOPNOTSUPP ; 
#define  MOD_LOAD 130 
#define  MOD_SHUTDOWN 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  atomic_load_acq_int (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cnadd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cnremove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  contigfree (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dcons_attach () ; 
 int /*<<< orphan*/  dcons_callout ; 
 int /*<<< orphan*/  dcons_close_refs ; 
 int /*<<< orphan*/  dcons_cninit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dcons_cnprobe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dcons_consdev ; 
 int /*<<< orphan*/  dcons_detach (int /*<<< orphan*/ ) ; 
 int dcons_drv_init (int) ; 
 TYPE_1__ dg ; 
 int drv_init ; 
 int /*<<< orphan*/  mstosbt (int) ; 
 int /*<<< orphan*/  pause_sbt (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
dcons_modevent(module_t mode, int type, void *data)
{
	int err = 0, ret;

	switch (type) {
	case MOD_LOAD:
		ret = dcons_drv_init(1);
		if (ret != -1)
			dcons_attach();
		if (ret == 0) {
			dcons_cnprobe(&dcons_consdev);
			dcons_cninit(&dcons_consdev);
			cnadd(&dcons_consdev);
		}
		break;
	case MOD_UNLOAD:
		printf("dcons: unload\n");
		if (drv_init == 1) {
			callout_stop(&dcons_callout);
			cnremove(&dcons_consdev);
			dcons_detach(DCONS_CON);
			dcons_detach(DCONS_GDB);
			dg.buf->magic = 0;

			contigfree(dg.buf, DCONS_BUF_SIZE, M_DEVBUF);
		}

		/* Wait for tty deferred free callbacks to complete. */
		while (atomic_load_acq_int(&dcons_close_refs) > 0)
                        pause_sbt("dcunld", mstosbt(50), mstosbt(10), 0);
		break;
	case MOD_SHUTDOWN:
#if 0		/* Keep connection after halt */
		dg.buf->magic = 0;
#endif
		break;
	default:
		err = EOPNOTSUPP;
		break;
	}
	return(err);
}