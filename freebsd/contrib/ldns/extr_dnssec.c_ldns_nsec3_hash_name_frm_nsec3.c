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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  ldns_rdf ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_FREE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_nsec3_algorithm (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * ldns_nsec3_hash_name (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_nsec3_iterations (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * ldns_nsec3_salt_data (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_nsec3_salt_length (int /*<<< orphan*/  const*) ; 

ldns_rdf *
ldns_nsec3_hash_name_frm_nsec3(const ldns_rr *nsec, const ldns_rdf *name)
{
	uint8_t algorithm;
	uint16_t iterations;
	uint8_t salt_length;
	uint8_t *salt = 0;

	ldns_rdf *hashed_owner;

	algorithm = ldns_nsec3_algorithm(nsec);
	salt_length = ldns_nsec3_salt_length(nsec);
	salt = ldns_nsec3_salt_data(nsec);
	iterations = ldns_nsec3_iterations(nsec);

	hashed_owner = ldns_nsec3_hash_name(name,
								 algorithm,
								 iterations,
								 salt_length,
								 salt);

	LDNS_FREE(salt);
	return hashed_owner;
}