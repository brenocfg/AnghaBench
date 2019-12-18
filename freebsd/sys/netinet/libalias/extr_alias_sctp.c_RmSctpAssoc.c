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
struct sctp_nat_assoc {int TableRegister; } ;
struct libalias {int packetAliasMode; int /*<<< orphan*/  sctpLinkCount; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIBALIAS_LOCK_ASSERT (struct libalias*) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct sctp_nat_assoc*,int /*<<< orphan*/ ) ; 
 int PKT_ALIAS_LOG ; 
 int SN_BOTH_TBL ; 
 int SN_GLOBAL_TBL ; 
 int SN_LOCAL_TBL ; 
 int /*<<< orphan*/  SN_LOG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SN_LOG_INFO ; 
 int /*<<< orphan*/  SN_LOG_LOW ; 
 int /*<<< orphan*/  SN_TO_NODIR ; 
 int /*<<< orphan*/  SctpShowAliasStats (struct libalias*) ; 
 int /*<<< orphan*/  list_G ; 
 int /*<<< orphan*/  list_L ; 
 int /*<<< orphan*/  logsctpassoc (struct sctp_nat_assoc*,char*) ; 
 int /*<<< orphan*/  logsctperror (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
RmSctpAssoc(struct libalias *la, struct sctp_nat_assoc *assoc)
{
	//  struct sctp_nat_assoc *found;
	if (assoc == NULL) {
		/* very bad, log and die*/
		SN_LOG(SN_LOG_LOW,
		    logsctperror("ERROR: alias_sctp:RmSctpAssoc(NULL)\n", 0, 0, SN_TO_NODIR));
		return;
	}
	/* log if association is fully up and now closing */
	if (assoc->TableRegister == SN_BOTH_TBL) {
		SN_LOG(SN_LOG_INFO, logsctpassoc(assoc, "$"));
	}
	LIBALIAS_LOCK_ASSERT(la);
	if (assoc->TableRegister & SN_LOCAL_TBL) {
		assoc->TableRegister ^= SN_LOCAL_TBL;
		la->sctpLinkCount--; //decrement link count
		LIST_REMOVE(assoc, list_L);
	}

	if (assoc->TableRegister & SN_GLOBAL_TBL) {
		assoc->TableRegister ^= SN_GLOBAL_TBL;
		la->sctpLinkCount--; //decrement link count
		LIST_REMOVE(assoc, list_G);
	}
	//  sn_free(assoc); //Don't remove now, remove if needed later
	/* libalias logging -- controlled by libalias log definition */
	if (la->packetAliasMode & PKT_ALIAS_LOG)
		SctpShowAliasStats(la);
}