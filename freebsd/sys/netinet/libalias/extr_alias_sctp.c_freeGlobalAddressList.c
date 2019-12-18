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
struct sctp_nat_assoc {int /*<<< orphan*/  Gaddr; } ;
struct sctp_GlobalAddress {int dummy; } ;

/* Variables and functions */
 struct sctp_GlobalAddress* LIST_FIRST (int /*<<< orphan*/ *) ; 
 struct sctp_GlobalAddress* LIST_NEXT (struct sctp_GlobalAddress*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_Gaddr ; 
 int /*<<< orphan*/  sn_free (struct sctp_GlobalAddress*) ; 

__attribute__((used)) static void freeGlobalAddressList(struct sctp_nat_assoc *assoc)
{
	struct sctp_GlobalAddress *gaddr1=NULL,*gaddr2=NULL;
	/*free global address list*/
	gaddr1 = LIST_FIRST(&(assoc->Gaddr));
	while (gaddr1 != NULL) {
		gaddr2 = LIST_NEXT(gaddr1, list_Gaddr);
		sn_free(gaddr1);
		gaddr1 = gaddr2;
	}
}