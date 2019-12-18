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
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_9__ {int is_vport; int /*<<< orphan*/  sm; void* ini_data; void* tgt_data; } ;
typedef  TYPE_1__ ocs_sport_t ;
struct TYPE_10__ {TYPE_4__* ocs; } ;
typedef  TYPE_2__ ocs_domain_t ;
typedef  int int32_t ;
struct TYPE_11__ {scalar_t__ enable_ini; scalar_t__ enable_tgt; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ocs_sport_vport_init ; 
 int /*<<< orphan*/  ocs_log_test (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  ocs_sm_transition (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* ocs_sport_alloc (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ ocs_vport_create_spec (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,void*,void*) ; 
 int ocs_vport_start (TYPE_2__*) ; 

int32_t
ocs_sport_vport_new(ocs_domain_t *domain, uint64_t wwpn, uint64_t wwnn,
		    uint32_t fc_id, uint8_t ini, uint8_t tgt, void *tgt_data,
		    void *ini_data, uint8_t restore_vport)
{
	ocs_sport_t *sport;

	if (ini && (domain->ocs->enable_ini == 0)) {
		ocs_log_test(domain->ocs, "driver initiator functionality not enabled\n");
		return -1;
	}

	if (tgt && (domain->ocs->enable_tgt == 0)) {
		ocs_log_test(domain->ocs, "driver target functionality not enabled\n");
		return -1;
	}

	/* Create a vport spec if we need to recreate this vport after a link up event */
	if (restore_vport) {
		if (ocs_vport_create_spec(domain->ocs, wwnn, wwpn, fc_id, ini, tgt, tgt_data, ini_data)) {
			ocs_log_test(domain->ocs, "failed to create vport object entry\n");
			return -1;
		}
		return ocs_vport_start(domain);
	}

	/* Allocate a sport */
	sport = ocs_sport_alloc(domain, wwpn, wwnn, fc_id, ini, tgt);

	if (sport == NULL) {
		return -1;
	}

	sport->is_vport = 1;
	sport->tgt_data = tgt_data;
	sport->ini_data = ini_data;
	
	/* Transition to vport_init */
	ocs_sm_transition(&sport->sm, __ocs_sport_vport_init, NULL);

	return 0;
}