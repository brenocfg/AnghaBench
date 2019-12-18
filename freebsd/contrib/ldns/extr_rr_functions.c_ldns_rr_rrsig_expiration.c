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
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  ldns_rdf ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_TYPE_RRSIG ; 
 int /*<<< orphan*/ * ldns_rr_function (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

ldns_rdf *
ldns_rr_rrsig_expiration(const ldns_rr *r)
{
	return ldns_rr_function(LDNS_RR_TYPE_RRSIG, r, 4);
}