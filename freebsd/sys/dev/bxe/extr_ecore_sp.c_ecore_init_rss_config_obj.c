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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct ecore_rss_config_obj {int /*<<< orphan*/  config_rss; int /*<<< orphan*/  engine_id; int /*<<< orphan*/  raw; } ;
struct bxe_softc {int dummy; } ;
typedef  int /*<<< orphan*/  ecore_obj_type ;
typedef  int /*<<< orphan*/  ecore_dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ecore_init_raw_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int,unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_setup_rss ; 

void ecore_init_rss_config_obj(struct bxe_softc *sc,
			       struct ecore_rss_config_obj *rss_obj,
			       uint8_t cl_id, uint32_t cid, uint8_t func_id, uint8_t engine_id,
			       void *rdata, ecore_dma_addr_t rdata_mapping,
			       int state, unsigned long *pstate,
			       ecore_obj_type type)
{
	ecore_init_raw_obj(&rss_obj->raw, cl_id, cid, func_id, rdata,
			   rdata_mapping, state, pstate, type);

	rss_obj->engine_id  = engine_id;
	rss_obj->config_rss = ecore_setup_rss;
}