#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint ;
struct snmp_value {int /*<<< orphan*/  var; } ;
struct snmp_context {TYPE_1__* scratch; } ;
struct bridge_if {int if_status; int /*<<< orphan*/  bif_name; } ;
struct TYPE_2__ {int int1; } ;

/* Variables and functions */
#define  RowStatus_active 130 
#define  RowStatus_destroy 129 
#define  RowStatus_notInService 128 
 int SNMP_ERR_GENERR ; 
 int SNMP_ERR_NOERROR ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  bridge_if_destroy (struct bridge_if*) ; 
 struct bridge_if* bridge_if_index_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bridge_set_if_up (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
bridge_rollback_if_status(struct snmp_context *ctx,
	struct snmp_value *val, uint sub)
{
	struct bridge_if *bif;

	if ((bif = bridge_if_index_get(&val->var, sub)) == NULL)
		return (SNMP_ERR_GENERR);

	switch (ctx->scratch->int1) {
		case RowStatus_destroy:
			bridge_if_destroy(bif);
			return (SNMP_ERR_NOERROR);

		case RowStatus_notInService:
			if (bif->if_status != ctx->scratch->int1)
				bridge_set_if_up(bif->bif_name, 0);
			bif->if_status = RowStatus_notInService;
			return (SNMP_ERR_NOERROR);

		case RowStatus_active:
			if (bif->if_status != ctx->scratch->int1)
				bridge_set_if_up(bif->bif_name, 1);
			bif->if_status = RowStatus_active;
			return (SNMP_ERR_NOERROR);
	}

	abort();
}