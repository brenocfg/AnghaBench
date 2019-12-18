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
typedef  int /*<<< orphan*/  uint8_t ;
struct ub_packed_rrset_key {int dummy; } ;
struct query_info {int /*<<< orphan*/  qname; } ;

/* Variables and functions */
 int /*<<< orphan*/ * nsec_closest_encloser (int /*<<< orphan*/ ,struct ub_packed_rrset_key*) ; 
 scalar_t__ query_dname_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  val_nsec_proves_name_error (struct ub_packed_rrset_key*,int /*<<< orphan*/ ) ; 

int val_nsec_proves_positive_wildcard(struct ub_packed_rrset_key* nsec, 
	struct query_info* qinf, uint8_t* wc)
{
	uint8_t* ce;
	/*  1) prove that qname doesn't exist and 
	 *  2) that the correct wildcard was used
	 *  nsec has been verified already. */
	if(!val_nsec_proves_name_error(nsec, qinf->qname))
		return 0;
	/* check wildcard name */
	ce = nsec_closest_encloser(qinf->qname, nsec);
	if(!ce)
		return 0;
	if(query_dname_compare(wc, ce) != 0) {
		return 0;
	}
	return 1;
}