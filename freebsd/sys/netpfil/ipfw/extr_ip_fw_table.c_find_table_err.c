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
struct tid_info {int uidx; int /*<<< orphan*/  set; int /*<<< orphan*/  tlen; int /*<<< orphan*/ * tlvs; } ;
struct table_config {int dummy; } ;
struct namedobj_instance {int dummy; } ;
struct named_object {int dummy; } ;
struct TYPE_3__ {char* name; } ;
typedef  TYPE_1__ ipfw_obj_ntlv ;
typedef  int /*<<< orphan*/  bname ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IPFW_TLV_TBL_NAME ; 
 scalar_t__ V_fw_tables_sets ; 
 TYPE_1__* ipfw_find_name_tlv_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct named_object* ipfw_objhash_lookup_name (struct namedobj_instance*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int
find_table_err(struct namedobj_instance *ni, struct tid_info *ti,
    struct table_config **tc)
{
	char *name, bname[16];
	struct named_object *no;
	ipfw_obj_ntlv *ntlv;
	uint32_t set;

	if (ti->tlvs != NULL) {
		ntlv = ipfw_find_name_tlv_type(ti->tlvs, ti->tlen, ti->uidx,
		    IPFW_TLV_TBL_NAME);
		if (ntlv == NULL)
			return (EINVAL);
		name = ntlv->name;

		/*
		 * Use set provided by @ti instead of @ntlv one.
		 * This is needed due to different sets behavior
		 * controlled by V_fw_tables_sets.
		 */
		set = (V_fw_tables_sets != 0) ? ti->set : 0;
	} else {
		snprintf(bname, sizeof(bname), "%d", ti->uidx);
		name = bname;
		set = 0;
	}

	no = ipfw_objhash_lookup_name(ni, set, name);
	*tc = (struct table_config *)no;

	return (0);
}