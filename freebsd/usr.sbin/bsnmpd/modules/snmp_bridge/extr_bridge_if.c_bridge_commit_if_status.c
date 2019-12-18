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
typedef  int /*<<< orphan*/  uint ;
struct snmp_value {int /*<<< orphan*/  var; } ;
struct bridge_if {scalar_t__ if_status; } ;

/* Variables and functions */
 scalar_t__ RowStatus_destroy ; 
 int SNMP_ERR_COMMIT_FAILED ; 
 int SNMP_ERR_GENERR ; 
 int SNMP_ERR_NOERROR ; 
 scalar_t__ bridge_if_destroy (struct bridge_if*) ; 
 struct bridge_if* bridge_if_index_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bridge_commit_if_status(struct snmp_value *val, uint sub)
{
	struct bridge_if *bif;

	if ((bif = bridge_if_index_get(&val->var, sub)) == NULL)
		return (SNMP_ERR_GENERR);

	if (bif->if_status == RowStatus_destroy &&
	    bridge_if_destroy(bif) < 0)
		return (SNMP_ERR_COMMIT_FAILED);

	return (SNMP_ERR_NOERROR);
}