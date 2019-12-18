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
struct tid_info {int /*<<< orphan*/  type; } ;
struct sockopt_data {int valsize; scalar_t__ kbuf; } ;
struct namedobj_instance {int dummy; } ;
struct ip_fw_chain {int dummy; } ;
struct TYPE_4__ {char* name; } ;
struct _ipfw_obj_header {TYPE_1__ ntlv; } ;
struct TYPE_5__ {char* algoname; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ ipfw_xtable_info ;
typedef  int /*<<< orphan*/  ip_fw3_opheader ;

/* Variables and functions */
 struct namedobj_instance* CHAIN_TO_NI (struct ip_fw_chain*) ; 
 int EEXIST ; 
 int EINVAL ; 
 int /*<<< orphan*/  IPFW_UH_RLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_UH_RUNLOCK (struct ip_fw_chain*) ; 
 scalar_t__ check_table_name (char*) ; 
 int create_table_internal (struct ip_fw_chain*,struct tid_info*,char*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * find_table (struct namedobj_instance*,struct tid_info*) ; 
 int /*<<< orphan*/  objheader_to_ti (struct _ipfw_obj_header*,struct tid_info*) ; 
 int strnlen (char*,int) ; 

__attribute__((used)) static int
create_table(struct ip_fw_chain *ch, ip_fw3_opheader *op3,
    struct sockopt_data *sd)
{
	struct _ipfw_obj_header *oh;
	ipfw_xtable_info *i;
	char *tname, *aname;
	struct tid_info ti;
	struct namedobj_instance *ni;

	if (sd->valsize != sizeof(*oh) + sizeof(ipfw_xtable_info))
		return (EINVAL);

	oh = (struct _ipfw_obj_header *)sd->kbuf;
	i = (ipfw_xtable_info *)(oh + 1);

	/*
	 * Verify user-supplied strings.
	 * Check for null-terminated/zero-length strings/
	 */
	tname = oh->ntlv.name;
	aname = i->algoname;
	if (check_table_name(tname) != 0 ||
	    strnlen(aname, sizeof(i->algoname)) == sizeof(i->algoname))
		return (EINVAL);

	if (aname[0] == '\0') {
		/* Use default algorithm */
		aname = NULL;
	}

	objheader_to_ti(oh, &ti);
	ti.type = i->type;

	ni = CHAIN_TO_NI(ch);

	IPFW_UH_RLOCK(ch);
	if (find_table(ni, &ti) != NULL) {
		IPFW_UH_RUNLOCK(ch);
		return (EEXIST);
	}
	IPFW_UH_RUNLOCK(ch);

	return (create_table_internal(ch, &ti, aname, i, NULL, 0));
}