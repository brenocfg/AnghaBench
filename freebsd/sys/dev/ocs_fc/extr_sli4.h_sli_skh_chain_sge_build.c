#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  uintptr_t uint32_t ;
struct TYPE_10__ {uintptr_t chain_sge_initial_value_lo; uintptr_t sgl_index_field_mask; uintptr_t sgl_index_field_offset; uintptr_t frag_num_field_mask; uintptr_t frag_num_field_offset; scalar_t__ chain_sge_initial_value_hi; } ;
struct TYPE_8__ {TYPE_3__ sgl_chaining_params; } ;
struct TYPE_9__ {TYPE_1__ config; } ;
typedef  TYPE_2__ sli4_t ;
typedef  TYPE_3__ sli4_sgl_chaining_params_t ;
struct TYPE_11__ {uintptr_t buffer_address_high; uintptr_t buffer_address_low; int /*<<< orphan*/  sge_type; } ;
typedef  TYPE_4__ sli4_sge_t ;

/* Variables and functions */
 int /*<<< orphan*/  SLI4_SGE_TYPE_CHAIN ; 
 int /*<<< orphan*/  ocs_memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
sli_skh_chain_sge_build(sli4_t *sli4, sli4_sge_t *sge, uint32_t xri_index, uint32_t frag_num, uint32_t offset)
{
	sli4_sgl_chaining_params_t *cparms = &sli4->config.sgl_chaining_params;


	ocs_memset(sge, 0, sizeof(*sge));
	sge->sge_type = SLI4_SGE_TYPE_CHAIN;
	sge->buffer_address_high = (uint32_t)cparms->chain_sge_initial_value_hi;
	sge->buffer_address_low =
		(uint32_t)((cparms->chain_sge_initial_value_lo |
			    (((uintptr_t)(xri_index & cparms->sgl_index_field_mask)) <<
			     cparms->sgl_index_field_offset) |
			    (((uintptr_t)(frag_num & cparms->frag_num_field_mask)) <<
			     cparms->frag_num_field_offset)  |
			    offset) >> 3);
}