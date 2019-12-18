#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  tgt_data; int /*<<< orphan*/  enable_tgt; int /*<<< orphan*/  enable_ini; int /*<<< orphan*/  wwnn; int /*<<< orphan*/  wwpn; TYPE_2__* sport; } ;
typedef  TYPE_1__ ocs_vport_spec_t ;
struct TYPE_6__ {int is_vport; int /*<<< orphan*/  sm; int /*<<< orphan*/  ini_data; int /*<<< orphan*/  tgt_data; } ;
typedef  TYPE_2__ ocs_sport_t ;
typedef  int /*<<< orphan*/  ocs_domain_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  UINT32_MAX ; 
 int /*<<< orphan*/  __ocs_sport_vport_init ; 
 int /*<<< orphan*/  ocs_assert (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocs_sm_transition (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* ocs_sport_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int32_t
ocs_sport_vport_alloc(ocs_domain_t *domain, ocs_vport_spec_t *vport)
{
	ocs_sport_t *sport = NULL;

	if (domain == NULL) {
		return (0);
	}

	ocs_assert((vport->sport == NULL), -1);	

	/* Allocate a sport */
	vport->sport = sport = ocs_sport_alloc(domain, vport->wwpn, vport->wwnn, UINT32_MAX, vport->enable_ini, vport->enable_tgt);

	if (sport == NULL) {
		return -1;
	}

	sport->is_vport = 1;
	sport->tgt_data = vport->tgt_data;
	sport->ini_data = vport->tgt_data;

	/* Transition to vport_init */
	ocs_sm_transition(&sport->sm, __ocs_sport_vport_init, NULL);

	return (0);
}