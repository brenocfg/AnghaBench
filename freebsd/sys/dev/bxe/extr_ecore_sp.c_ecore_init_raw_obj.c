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
typedef  void* uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct ecore_raw_obj {int state; unsigned long* pstate; int /*<<< orphan*/  wait_comp; int /*<<< orphan*/  set_pending; int /*<<< orphan*/  clear_pending; int /*<<< orphan*/  check_pending; int /*<<< orphan*/  obj_type; int /*<<< orphan*/  rdata_mapping; void* rdata; void* cl_id; int /*<<< orphan*/  cid; void* func_id; } ;
typedef  int /*<<< orphan*/  ecore_obj_type ;
typedef  int /*<<< orphan*/  ecore_dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ecore_raw_check_pending ; 
 int /*<<< orphan*/  ecore_raw_clear_pending ; 
 int /*<<< orphan*/  ecore_raw_set_pending ; 
 int /*<<< orphan*/  ecore_raw_wait ; 

__attribute__((used)) static inline void ecore_init_raw_obj(struct ecore_raw_obj *raw, uint8_t cl_id,
	uint32_t cid, uint8_t func_id, void *rdata, ecore_dma_addr_t rdata_mapping, int state,
	unsigned long *pstate, ecore_obj_type type)
{
	raw->func_id = func_id;
	raw->cid = cid;
	raw->cl_id = cl_id;
	raw->rdata = rdata;
	raw->rdata_mapping = rdata_mapping;
	raw->state = state;
	raw->pstate = pstate;
	raw->obj_type = type;
	raw->check_pending = ecore_raw_check_pending;
	raw->clear_pending = ecore_raw_clear_pending;
	raw->set_pending = ecore_raw_set_pending;
	raw->wait_comp = ecore_raw_wait;
}