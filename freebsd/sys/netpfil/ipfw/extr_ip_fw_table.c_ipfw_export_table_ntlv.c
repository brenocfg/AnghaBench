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
typedef  int /*<<< orphan*/  uint16_t ;
struct sockopt_data {int dummy; } ;
struct namedobj_instance {int dummy; } ;
struct named_object {int /*<<< orphan*/  name; int /*<<< orphan*/  kidx; } ;
struct ip_fw_chain {int dummy; } ;
struct TYPE_3__ {int length; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; int /*<<< orphan*/  idx; TYPE_1__ head; } ;
typedef  TYPE_2__ ipfw_obj_ntlv ;

/* Variables and functions */
 struct namedobj_instance* CHAIN_TO_NI (struct ip_fw_chain*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IPFW_TLV_TBL_NAME ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ipfw_get_sopt_space (struct sockopt_data*,int) ; 
 struct named_object* ipfw_objhash_lookup_kidx (struct namedobj_instance*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
ipfw_export_table_ntlv(struct ip_fw_chain *ch, uint16_t kidx,
    struct sockopt_data *sd)
{
	struct namedobj_instance *ni;
	struct named_object *no;
	ipfw_obj_ntlv *ntlv;

	ni = CHAIN_TO_NI(ch);

	no = ipfw_objhash_lookup_kidx(ni, kidx);
	KASSERT(no != NULL, ("invalid table kidx passed"));

	ntlv = (ipfw_obj_ntlv *)ipfw_get_sopt_space(sd, sizeof(*ntlv));
	if (ntlv == NULL)
		return (ENOMEM);

	ntlv->head.type = IPFW_TLV_TBL_NAME;
	ntlv->head.length = sizeof(*ntlv);
	ntlv->idx = no->kidx;
	strlcpy(ntlv->name, no->name, sizeof(ntlv->name));

	return (0);
}