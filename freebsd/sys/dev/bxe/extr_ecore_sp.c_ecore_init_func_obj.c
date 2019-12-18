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
struct ecore_func_sp_obj {struct ecore_func_sp_drv_ops* drv; int /*<<< orphan*/  wait_comp; int /*<<< orphan*/  complete_cmd; int /*<<< orphan*/  check_transition; int /*<<< orphan*/  send_cmd; void* afex_rdata_mapping; void* afex_rdata; void* rdata_mapping; void* rdata; int /*<<< orphan*/  one_pending_mutex; } ;
struct ecore_func_sp_drv_ops {int dummy; } ;
struct bxe_softc {int dummy; } ;
typedef  void* ecore_dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_MEMSET (struct ecore_func_sp_obj*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ECORE_MUTEX_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecore_func_chk_transition ; 
 int /*<<< orphan*/  ecore_func_comp_cmd ; 
 int /*<<< orphan*/  ecore_func_send_cmd ; 
 int /*<<< orphan*/  ecore_func_wait_comp ; 

void ecore_init_func_obj(struct bxe_softc *sc,
			 struct ecore_func_sp_obj *obj,
			 void *rdata, ecore_dma_addr_t rdata_mapping,
			 void *afex_rdata, ecore_dma_addr_t afex_rdata_mapping,
			 struct ecore_func_sp_drv_ops *drv_iface)
{
	ECORE_MEMSET(obj, 0, sizeof(*obj));

	ECORE_MUTEX_INIT(&obj->one_pending_mutex);

	obj->rdata = rdata;
	obj->rdata_mapping = rdata_mapping;
	obj->afex_rdata = afex_rdata;
	obj->afex_rdata_mapping = afex_rdata_mapping;
	obj->send_cmd = ecore_func_send_cmd;
	obj->check_transition = ecore_func_chk_transition;
	obj->complete_cmd = ecore_func_comp_cmd;
	obj->wait_comp = ecore_func_wait_comp;
	obj->drv = drv_iface;
}