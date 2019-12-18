#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint ;
struct TYPE_3__ {int integer; } ;
struct snmp_value {int /*<<< orphan*/  var; TYPE_1__ v; } ;
struct snmp_context {TYPE_2__* scratch; } ;
struct bridge_if {int if_status; int /*<<< orphan*/  bif_name; } ;
struct TYPE_4__ {int int1; } ;

/* Variables and functions */
 int IFNAMSIZ ; 
#define  RowStatus_active 133 
#define  RowStatus_createAndGo 132 
#define  RowStatus_createAndWait 131 
#define  RowStatus_destroy 130 
#define  RowStatus_notInService 129 
#define  RowStatus_notReady 128 
 int SNMP_ERR_BADVALUE ; 
 int SNMP_ERR_GENERR ; 
 int SNMP_ERR_INCONS_VALUE ; 
 int SNMP_ERR_NOERROR ; 
 int SNMP_ERR_NOSUCHNAME ; 
 int /*<<< orphan*/  bridge_if_create (char*,int) ; 
 struct bridge_if* bridge_if_index_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bridge_name_index_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bridge_set_if_up (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
bridge_set_if_status(struct snmp_context *ctx,
	struct snmp_value *val, uint sub)
{
	struct bridge_if *bif;
	char bif_name[IFNAMSIZ];

	bif = bridge_if_index_get(&val->var, sub);

	switch (val->v.integer) {
	    case RowStatus_active:
		if (bif == NULL)
		    return (SNMP_ERR_INCONS_VALUE);

		ctx->scratch->int1 = bif->if_status;

		switch (bif->if_status) {
		    case RowStatus_active:
			return (SNMP_ERR_NOERROR);
		    case RowStatus_notInService:
			if (bridge_set_if_up(bif->bif_name, 1) < 0)
			    return (SNMP_ERR_GENERR);
			return (SNMP_ERR_NOERROR);
		    default:
			break;
		}
		return (SNMP_ERR_INCONS_VALUE);

	    case RowStatus_notInService:
		if (bif == NULL)
		    return (SNMP_ERR_INCONS_VALUE);

		ctx->scratch->int1 = bif->if_status;

		switch (bif->if_status) {
		    case RowStatus_active:
			if (bridge_set_if_up(bif->bif_name, 1) < 0)
			    return (SNMP_ERR_GENERR);
			return (SNMP_ERR_NOERROR);
		    case RowStatus_notInService:
			return (SNMP_ERR_NOERROR);
		    default:
			break;
		}
		return (SNMP_ERR_INCONS_VALUE);

	    case RowStatus_notReady:
		return (SNMP_ERR_INCONS_VALUE);

	    case RowStatus_createAndGo:
		if (bif != NULL)
		    return (SNMP_ERR_INCONS_VALUE);

		ctx->scratch->int1 = RowStatus_destroy;

		if (bridge_name_index_get(&val->var, sub, bif_name) == NULL)
		    return (SNMP_ERR_BADVALUE);
		if (bridge_if_create(bif_name, 1) < 0)
		    return (SNMP_ERR_GENERR);
		return (SNMP_ERR_NOERROR);

	    case RowStatus_createAndWait:
		if (bif != NULL)
		    return (SNMP_ERR_INCONS_VALUE);

		if (bridge_name_index_get(&val->var, sub, bif_name) == NULL)
		    return (SNMP_ERR_BADVALUE);

		ctx->scratch->int1 = RowStatus_destroy;

		if (bridge_if_create(bif_name, 0) < 0)
		    return (SNMP_ERR_GENERR);
		return (SNMP_ERR_NOERROR);

	    case RowStatus_destroy:
		if (bif == NULL)
		    return (SNMP_ERR_NOSUCHNAME);

		ctx->scratch->int1 = bif->if_status;
		bif->if_status = RowStatus_destroy;
	}

	return (SNMP_ERR_NOERROR);
}