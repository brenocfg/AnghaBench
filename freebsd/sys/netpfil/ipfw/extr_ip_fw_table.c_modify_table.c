#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tid_info {int /*<<< orphan*/  type; } ;
struct table_config {int locked; int /*<<< orphan*/  limit; TYPE_2__* ta; } ;
struct sockopt_data {int valsize; scalar_t__ kbuf; } ;
struct namedobj_instance {int dummy; } ;
struct ip_fw_chain {int dummy; } ;
struct TYPE_4__ {char* name; } ;
struct _ipfw_obj_header {TYPE_1__ ntlv; } ;
struct TYPE_6__ {int mflags; int flags; int /*<<< orphan*/  limit; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ ipfw_xtable_info ;
typedef  int /*<<< orphan*/  ip_fw3_opheader ;
struct TYPE_5__ {int flags; } ;

/* Variables and functions */
 struct namedobj_instance* CHAIN_TO_NI (struct ip_fw_chain*) ; 
 int EACCES ; 
 int EINVAL ; 
 int ESRCH ; 
 int IPFW_TGFLAGS_LOCKED ; 
 int IPFW_TMFLAGS_LIMIT ; 
 int IPFW_TMFLAGS_LOCK ; 
 int /*<<< orphan*/  IPFW_UH_WLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_UH_WUNLOCK (struct ip_fw_chain*) ; 
 int TA_FLAG_READONLY ; 
 scalar_t__ check_table_name (char*) ; 
 struct table_config* find_table (struct namedobj_instance*,struct tid_info*) ; 
 int /*<<< orphan*/  objheader_to_ti (struct _ipfw_obj_header*,struct tid_info*) ; 

__attribute__((used)) static int
modify_table(struct ip_fw_chain *ch, ip_fw3_opheader *op3,
    struct sockopt_data *sd)
{
	struct _ipfw_obj_header *oh;
	ipfw_xtable_info *i;
	char *tname;
	struct tid_info ti;
	struct namedobj_instance *ni;
	struct table_config *tc;

	if (sd->valsize != sizeof(*oh) + sizeof(ipfw_xtable_info))
		return (EINVAL);

	oh = (struct _ipfw_obj_header *)sd->kbuf;
	i = (ipfw_xtable_info *)(oh + 1);

	/*
	 * Verify user-supplied strings.
	 * Check for null-terminated/zero-length strings/
	 */
	tname = oh->ntlv.name;
	if (check_table_name(tname) != 0)
		return (EINVAL);

	objheader_to_ti(oh, &ti);
	ti.type = i->type;

	IPFW_UH_WLOCK(ch);
	ni = CHAIN_TO_NI(ch);
	if ((tc = find_table(ni, &ti)) == NULL) {
		IPFW_UH_WUNLOCK(ch);
		return (ESRCH);
	}

	/* Do not support any modifications for readonly tables */
	if ((tc->ta->flags & TA_FLAG_READONLY) != 0) {
		IPFW_UH_WUNLOCK(ch);
		return (EACCES);
	}

	if ((i->mflags & IPFW_TMFLAGS_LIMIT) != 0)
		tc->limit = i->limit;
	if ((i->mflags & IPFW_TMFLAGS_LOCK) != 0)
		tc->locked = ((i->flags & IPFW_TGFLAGS_LOCKED) != 0);
	IPFW_UH_WUNLOCK(ch);

	return (0);
}