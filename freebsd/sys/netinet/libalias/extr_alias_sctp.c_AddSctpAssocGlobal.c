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
struct TYPE_2__ {scalar_t__ s_addr; } ;
struct sctp_nat_assoc {scalar_t__ l_port; int /*<<< orphan*/  TableRegister; int /*<<< orphan*/  g_port; int /*<<< orphan*/  g_vtag; TYPE_1__ l_addr; } ;
struct libalias {int packetAliasMode; int /*<<< orphan*/  sctpLinkCount; int /*<<< orphan*/  sctpNatTableSize; int /*<<< orphan*/ * sctpTableGlobal; } ;

/* Variables and functions */
 struct sctp_nat_assoc* FindSctpGlobalClash (struct libalias*,struct sctp_nat_assoc*) ; 
 int /*<<< orphan*/  LIBALIAS_LOCK_ASSERT (struct libalias*) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct sctp_nat_assoc*,int /*<<< orphan*/ ) ; 
 int PKT_ALIAS_LOG ; 
 int /*<<< orphan*/  RmSctpAssoc (struct libalias*,struct sctp_nat_assoc*) ; 
 int SN_ADD_CLASH ; 
 int SN_ADD_OK ; 
 int /*<<< orphan*/  SN_BOTH_TBL ; 
 int /*<<< orphan*/  SN_GLOBAL_TBL ; 
 int /*<<< orphan*/  SN_LOG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SN_LOG_INFO ; 
 size_t SN_TABLE_HASH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SctpShowAliasStats (struct libalias*) ; 
 int /*<<< orphan*/  freeGlobalAddressList (struct sctp_nat_assoc*) ; 
 int /*<<< orphan*/  list_G ; 
 int /*<<< orphan*/  logsctpassoc (struct sctp_nat_assoc*,char*) ; 
 int /*<<< orphan*/  sctp_RmTimeOut (struct libalias*,struct sctp_nat_assoc*) ; 
 int /*<<< orphan*/  sn_free (struct sctp_nat_assoc*) ; 

__attribute__((used)) static int
AddSctpAssocGlobal(struct libalias *la, struct sctp_nat_assoc *assoc)
{
	struct sctp_nat_assoc *found;

	LIBALIAS_LOCK_ASSERT(la);
	found = FindSctpGlobalClash(la, assoc);
	if (found != NULL) {
		if ((found->TableRegister == SN_GLOBAL_TBL) &&			\
		    (found->l_addr.s_addr == assoc->l_addr.s_addr) && (found->l_port == assoc->l_port)) { /* resent message */
			RmSctpAssoc(la, found);
			sctp_RmTimeOut(la, found);
			freeGlobalAddressList(found);
			sn_free(found);
		} else
			return (SN_ADD_CLASH);
	}

	LIST_INSERT_HEAD(&la->sctpTableGlobal[SN_TABLE_HASH(assoc->g_vtag, assoc->g_port, la->sctpNatTableSize)],
	    assoc, list_G);
	assoc->TableRegister |= SN_GLOBAL_TBL;
	la->sctpLinkCount++; //increment link count

	if (assoc->TableRegister == SN_BOTH_TBL) {
		/* libalias log -- controlled by libalias */
		if (la->packetAliasMode & PKT_ALIAS_LOG)
			SctpShowAliasStats(la);

		SN_LOG(SN_LOG_INFO, logsctpassoc(assoc, "^"));
	}

	return (SN_ADD_OK);
}