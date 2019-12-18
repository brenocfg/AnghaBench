#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct tid_info {int uidx; int /*<<< orphan*/  tlen; int /*<<< orphan*/ * tlvs; } ;
struct TYPE_4__ {scalar_t__ set; int /*<<< orphan*/  subtype; int /*<<< orphan*/  name; } ;
struct table_config {int vshared; int /*<<< orphan*/  ti_copy; int /*<<< orphan*/  astate; int /*<<< orphan*/  tablename; struct table_algo* ta; int /*<<< orphan*/  tflags; TYPE_1__ no; } ;
struct table_algo {int (* init ) (struct ip_fw_chain*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  type; } ;
struct ip_fw_chain {int dummy; } ;
struct TYPE_5__ {char* name; scalar_t__ set; } ;
typedef  TYPE_2__ ipfw_obj_ntlv ;
typedef  int /*<<< orphan*/  bname ;

/* Variables and functions */
 int /*<<< orphan*/  IPFW_TLV_TBL_NAME ; 
 int /*<<< orphan*/  M_IPFW ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 scalar_t__ V_fw_tables_sets ; 
 int /*<<< orphan*/  free (struct table_config*,int /*<<< orphan*/ ) ; 
 TYPE_2__* ipfw_find_name_tlv_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct table_config* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int stub1 (struct ip_fw_chain*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct table_config *
alloc_table_config(struct ip_fw_chain *ch, struct tid_info *ti,
    struct table_algo *ta, char *aname, uint8_t tflags)
{
	char *name, bname[16];
	struct table_config *tc;
	int error;
	ipfw_obj_ntlv *ntlv;
	uint32_t set;

	if (ti->tlvs != NULL) {
		ntlv = ipfw_find_name_tlv_type(ti->tlvs, ti->tlen, ti->uidx,
		    IPFW_TLV_TBL_NAME);
		if (ntlv == NULL)
			return (NULL);
		name = ntlv->name;
		set = (V_fw_tables_sets == 0) ? 0 : ntlv->set;
	} else {
		/* Compat part: convert number to string representation */
		snprintf(bname, sizeof(bname), "%d", ti->uidx);
		name = bname;
		set = 0;
	}

	tc = malloc(sizeof(struct table_config), M_IPFW, M_WAITOK | M_ZERO);
	tc->no.name = tc->tablename;
	tc->no.subtype = ta->type;
	tc->no.set = set;
	tc->tflags = tflags;
	tc->ta = ta;
	strlcpy(tc->tablename, name, sizeof(tc->tablename));
	/* Set "shared" value type by default */
	tc->vshared = 1;

	/* Preallocate data structures for new tables */
	error = ta->init(ch, &tc->astate, &tc->ti_copy, aname, tflags);
	if (error != 0) {
		free(tc, M_IPFW);
		return (NULL);
	}
	
	return (tc);
}