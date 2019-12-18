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
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  ldns_rdf ;

/* Variables and functions */
 int /*<<< orphan*/ * ldns_nsec3_salt (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * ldns_rdf_data (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_rdf_size (int /*<<< orphan*/ *) ; 

uint8_t
ldns_nsec3_salt_length(const ldns_rr *nsec3_rr)
{
	ldns_rdf *salt_rdf = ldns_nsec3_salt(nsec3_rr);
	if (salt_rdf && ldns_rdf_size(salt_rdf) > 0) {
		return (uint8_t) ldns_rdf_data(salt_rdf)[0];
	}
	return 0;
}