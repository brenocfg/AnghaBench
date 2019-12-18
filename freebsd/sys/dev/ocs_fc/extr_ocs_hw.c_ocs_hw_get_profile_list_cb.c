#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {scalar_t__ virt; } ;
struct TYPE_17__ {int num_descriptors; TYPE_8__ payload; int /*<<< orphan*/  arg; int /*<<< orphan*/  (* cb ) (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ;TYPE_1__* descriptors; } ;
typedef  TYPE_3__ uint8_t ;
struct TYPE_18__ {int profile_descriptor_count; TYPE_2__* profile_descriptor; } ;
typedef  TYPE_4__ sli4_res_common_get_profile_list_t ;
struct TYPE_19__ {int /*<<< orphan*/  os; } ;
typedef  TYPE_5__ ocs_hw_t ;
typedef  TYPE_3__ ocs_hw_profile_list_t ;
typedef  TYPE_3__ ocs_hw_get_profile_list_cb_arg_t ;
typedef  TYPE_8__ ocs_dma_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_16__ {scalar_t__ profile_description; int /*<<< orphan*/  profile_index; int /*<<< orphan*/  profile_id; } ;
struct TYPE_15__ {int /*<<< orphan*/  profile_description; int /*<<< orphan*/  profile_index; int /*<<< orphan*/  profile_id; } ;

/* Variables and functions */
 int OCS_HW_MAX_PROFILES ; 
 int /*<<< orphan*/  OCS_M_ZERO ; 
 int SLI4_BMBX_SIZE ; 
 int /*<<< orphan*/  ocs_dma_free (int /*<<< orphan*/ ,TYPE_8__*) ; 
 int /*<<< orphan*/  ocs_free (int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 TYPE_3__* ocs_malloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t
ocs_hw_get_profile_list_cb(ocs_hw_t *hw, int32_t status, uint8_t *mqe, void *arg)
{
	ocs_hw_profile_list_t *list;
	ocs_hw_get_profile_list_cb_arg_t *cb_arg = arg;
	ocs_dma_t *payload = &(cb_arg->payload);
	sli4_res_common_get_profile_list_t *response = (sli4_res_common_get_profile_list_t *)payload->virt;
	int i;
	int num_descriptors;

	list = ocs_malloc(hw->os, sizeof(ocs_hw_profile_list_t), OCS_M_ZERO);
	list->num_descriptors = response->profile_descriptor_count;

	num_descriptors = list->num_descriptors;
	if (num_descriptors > OCS_HW_MAX_PROFILES) {
		num_descriptors = OCS_HW_MAX_PROFILES;
	}

	for (i=0; i<num_descriptors; i++) {
		list->descriptors[i].profile_id = response->profile_descriptor[i].profile_id;
		list->descriptors[i].profile_index = response->profile_descriptor[i].profile_index;
		ocs_strcpy(list->descriptors[i].profile_description, (char *)response->profile_descriptor[i].profile_description);
	}

	if (cb_arg->cb) {
		cb_arg->cb(status, list, cb_arg->arg);
	} else {
		ocs_free(hw->os, list, sizeof(*list));
	}

	ocs_free(hw->os, mqe, SLI4_BMBX_SIZE);
	ocs_dma_free(hw->os, &cb_arg->payload);
	ocs_free(hw->os, cb_arg, sizeof(ocs_hw_get_profile_list_cb_arg_t));

	return 0;
}