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
typedef  int /*<<< orphan*/  ldns_rr_type ;
typedef  int /*<<< orphan*/  ldns_rr ;

/* Variables and functions */
#define  LDNS_RR_TYPE_NSEC 129 
#define  LDNS_RR_TYPE_NSEC3 128 
 int ldns_nsec_bitmap_covers_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ldns_rr_get_type (int /*<<< orphan*/  const*) ; 
 int ldns_rr_rd_count (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rr_rdf (int /*<<< orphan*/  const*,int) ; 

bool
ldns_nsec_type_check(const ldns_rr *nsec, ldns_rr_type t)
{
	switch (ldns_rr_get_type(nsec)) {
	case LDNS_RR_TYPE_NSEC	: if (ldns_rr_rd_count(nsec) < 2) {
					  return false;
				  }
				  return ldns_nsec_bitmap_covers_type(
						  ldns_rr_rdf(nsec, 1), t);

	case LDNS_RR_TYPE_NSEC3	: if (ldns_rr_rd_count(nsec) < 6) {
					  return false;
				  }
				  return ldns_nsec_bitmap_covers_type(
						  ldns_rr_rdf(nsec, 5), t);

	default			: return false;
	}
}