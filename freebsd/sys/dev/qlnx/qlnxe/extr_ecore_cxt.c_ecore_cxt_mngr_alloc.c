#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_8__ {int /*<<< orphan*/  val; void* reg; } ;
struct TYPE_7__ {void* reg; } ;
struct TYPE_6__ {void* reg; } ;
struct ecore_ilt_client_cfg {TYPE_3__ p_size; TYPE_2__ last; TYPE_1__ first; } ;
struct ecore_hwfn {struct ecore_cxt_mngr* p_cxt_mngr; TYPE_5__* p_dev; } ;
struct ecore_cxt_mngr {int /*<<< orphan*/  mutex; int /*<<< orphan*/  vf_count; int /*<<< orphan*/ * task_type_size; struct ecore_ilt_client_cfg* clients; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_10__ {TYPE_4__* p_iov_info; int /*<<< orphan*/  ilt_page_size; } ;
struct TYPE_9__ {int /*<<< orphan*/  total_vfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDUC ; 
 int /*<<< orphan*/  CDUT ; 
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*) ; 
 int ECORE_NOMEM ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  FIRST_ILT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* ILT_CFG_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t ILT_CLI_CDUC ; 
 size_t ILT_CLI_CDUT ; 
 size_t ILT_CLI_MAX ; 
 size_t ILT_CLI_QM ; 
 size_t ILT_CLI_SRC ; 
 size_t ILT_CLI_TM ; 
 size_t ILT_CLI_TSDM ; 
 int /*<<< orphan*/  LAST_ILT ; 
 int /*<<< orphan*/  OSAL_MUTEX_ALLOC (struct ecore_hwfn*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSAL_MUTEX_INIT (int /*<<< orphan*/ *) ; 
 struct ecore_cxt_mngr* OSAL_ZALLOC (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  P_SIZE ; 
 int /*<<< orphan*/  QM ; 
 int /*<<< orphan*/  SRC ; 
 int /*<<< orphan*/  TM ; 
 int /*<<< orphan*/  TSDM ; 
 int /*<<< orphan*/  TYPE0_TASK_CXT_SIZE (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  TYPE1_TASK_CXT_SIZE (struct ecore_hwfn*) ; 

enum _ecore_status_t ecore_cxt_mngr_alloc(struct ecore_hwfn *p_hwfn)
{
	struct ecore_ilt_client_cfg *clients;
	struct ecore_cxt_mngr *p_mngr;
	u32 i;

	p_mngr = OSAL_ZALLOC(p_hwfn->p_dev, GFP_KERNEL, sizeof(*p_mngr));
	if (!p_mngr) {
		DP_NOTICE(p_hwfn, false, "Failed to allocate `struct ecore_cxt_mngr'\n");
		return ECORE_NOMEM;
	}

	/* Initialize ILT client registers */
	clients = p_mngr->clients;
	clients[ILT_CLI_CDUC].first.reg = ILT_CFG_REG(CDUC, FIRST_ILT);
	clients[ILT_CLI_CDUC].last.reg  = ILT_CFG_REG(CDUC, LAST_ILT);
	clients[ILT_CLI_CDUC].p_size.reg = ILT_CFG_REG(CDUC, P_SIZE);

	clients[ILT_CLI_QM].first.reg   = ILT_CFG_REG(QM, FIRST_ILT);
	clients[ILT_CLI_QM].last.reg    = ILT_CFG_REG(QM, LAST_ILT);
	clients[ILT_CLI_QM].p_size.reg  = ILT_CFG_REG(QM, P_SIZE);

	clients[ILT_CLI_TM].first.reg   = ILT_CFG_REG(TM, FIRST_ILT);
	clients[ILT_CLI_TM].last.reg    = ILT_CFG_REG(TM, LAST_ILT);
	clients[ILT_CLI_TM].p_size.reg  = ILT_CFG_REG(TM, P_SIZE);

	clients[ILT_CLI_SRC].first.reg  = ILT_CFG_REG(SRC, FIRST_ILT);
	clients[ILT_CLI_SRC].last.reg   = ILT_CFG_REG(SRC, LAST_ILT);
	clients[ILT_CLI_SRC].p_size.reg = ILT_CFG_REG(SRC, P_SIZE);

	clients[ILT_CLI_CDUT].first.reg = ILT_CFG_REG(CDUT, FIRST_ILT);
	clients[ILT_CLI_CDUT].last.reg  = ILT_CFG_REG(CDUT, LAST_ILT);
	clients[ILT_CLI_CDUT].p_size.reg = ILT_CFG_REG(CDUT, P_SIZE);

	clients[ILT_CLI_TSDM].first.reg = ILT_CFG_REG(TSDM, FIRST_ILT);
	clients[ILT_CLI_TSDM].last.reg  = ILT_CFG_REG(TSDM, LAST_ILT);
	clients[ILT_CLI_TSDM].p_size.reg = ILT_CFG_REG(TSDM, P_SIZE);

	/* default ILT page size for all clients is 64K */
	for (i = 0; i < ILT_CLI_MAX; i++)
		p_mngr->clients[i].p_size.val = p_hwfn->p_dev->ilt_page_size;

	/* Initialize task sizes */
	p_mngr->task_type_size[0] = TYPE0_TASK_CXT_SIZE(p_hwfn);
	p_mngr->task_type_size[1] = TYPE1_TASK_CXT_SIZE(p_hwfn);

	if (p_hwfn->p_dev->p_iov_info)
		p_mngr->vf_count = p_hwfn->p_dev->p_iov_info->total_vfs;

	/* Initialize the dynamic ILT allocation mutex */
#ifdef CONFIG_ECORE_LOCK_ALLOC
	OSAL_MUTEX_ALLOC(p_hwfn, &p_mngr->mutex);
#endif
	OSAL_MUTEX_INIT(&p_mngr->mutex);

	/* Set the cxt mangr pointer priori to further allocations */
	p_hwfn->p_cxt_mngr = p_mngr;

	return ECORE_SUCCESS;
}