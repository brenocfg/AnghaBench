#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct tid_info {int /*<<< orphan*/  set; int /*<<< orphan*/  uidx; int /*<<< orphan*/  tlen; int /*<<< orphan*/ * tlvs; } ;
struct namedobj_instance {int dummy; } ;
struct named_object {int dummy; } ;
struct TYPE_3__ {char* name; } ;
typedef  TYPE_1__ ipfw_obj_ntlv ;

/* Variables and functions */
 int EINVAL ; 
 int ESRCH ; 
 TYPE_1__* ipfw_find_name_tlv_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct named_object* ipfw_objhash_lookup_name (struct namedobj_instance*,int /*<<< orphan*/ ,char*) ; 

int
ipfw_objhash_find_type(struct namedobj_instance *ni, struct tid_info *ti,
    uint32_t etlv, struct named_object **pno)
{
	char *name;
	ipfw_obj_ntlv *ntlv;
	uint32_t set;

	if (ti->tlvs == NULL)
		return (EINVAL);

	ntlv = ipfw_find_name_tlv_type(ti->tlvs, ti->tlen, ti->uidx, etlv);
	if (ntlv == NULL)
		return (EINVAL);
	name = ntlv->name;

	/*
	 * Use set provided by @ti instead of @ntlv one.
	 * This is needed due to different sets behavior
	 * controlled by V_fw_tables_sets.
	 */
	set = ti->set;
	*pno = ipfw_objhash_lookup_name(ni, set, name);
	if (*pno == NULL)
		return (ESRCH);
	return (0);
}