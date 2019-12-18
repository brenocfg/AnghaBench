#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int hard_flush; } ;
struct TYPE_21__ {int* priv; scalar_t__ Result; int /*<<< orphan*/  done; TYPE_7__* target; TYPE_6__ flags; int /*<<< orphan*/  type; } ;
struct TYPE_17__ {TYPE_3__* transform; } ;
struct TYPE_18__ {TYPE_4__ array; } ;
struct TYPE_20__ {int /*<<< orphan*/  vbus; int /*<<< orphan*/  cmds_per_request; TYPE_5__ u; int /*<<< orphan*/  type; } ;
struct TYPE_16__ {TYPE_2__* target; TYPE_1__* source; } ;
struct TYPE_15__ {int /*<<< orphan*/  cmds_per_request; } ;
struct TYPE_14__ {int /*<<< orphan*/  cmds_per_request; } ;
typedef  TYPE_7__* PVDEV ;
typedef  int /*<<< orphan*/  PVBUS_EXT ;
typedef  TYPE_8__* PCOMMAND ;
typedef  int /*<<< orphan*/  HPT_UINT ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_TYPE_FLUSH ; 
 int /*<<< orphan*/  HPT_OSM_TIMEOUT ; 
 int /*<<< orphan*/  KdPrint (char*) ; 
 int /*<<< orphan*/  PPAUSE ; 
 scalar_t__ RETURN_SUCCESS ; 
 int /*<<< orphan*/  hpt_assert_vbus_locked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpt_flush_done ; 
 scalar_t__ hpt_sleep (int /*<<< orphan*/ ,TYPE_8__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_8__* ldm_alloc_cmds (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldm_free_cmds (TYPE_8__*) ; 
 int /*<<< orphan*/  ldm_queue_cmd (TYPE_8__*) ; 
 int /*<<< orphan*/  ldm_reset_vbus (int /*<<< orphan*/ ) ; 
 scalar_t__ mIsArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hpt_flush_vdev(PVBUS_EXT vbus_ext, PVDEV vd)
{
	PCOMMAND pCmd;
	int result = 0, done;
	HPT_UINT count;

	KdPrint(("flusing dev %p", vd));

	hpt_assert_vbus_locked(vbus_ext);

	if (mIsArray(vd->type) && vd->u.array.transform)
		count = max(vd->u.array.transform->source->cmds_per_request,
					vd->u.array.transform->target->cmds_per_request);
	else
		count = vd->cmds_per_request;

	pCmd = ldm_alloc_cmds(vd->vbus, count);

	if (!pCmd) {
		return -1;
	}

	pCmd->type = CMD_TYPE_FLUSH;
	pCmd->flags.hard_flush = 1;
	pCmd->target = vd;
	pCmd->done = hpt_flush_done;
	done = 0;
	pCmd->priv = &done;

	ldm_queue_cmd(pCmd);
	
	if (!done) {
		while (hpt_sleep(vbus_ext, pCmd, PPAUSE, "hptfls", HPT_OSM_TIMEOUT)) {
			ldm_reset_vbus(vd->vbus);
		}
	}

	KdPrint(("flush result %d", pCmd->Result));

	if (pCmd->Result!=RETURN_SUCCESS)
		result = -1;

	ldm_free_cmds(pCmd);

	return result;
}