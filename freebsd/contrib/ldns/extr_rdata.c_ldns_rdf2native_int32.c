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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ldns_rdf ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 scalar_t__ LDNS_RDF_SIZE_DOUBLEWORD ; 
 int /*<<< orphan*/  ldns_rdf_data (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_rdf_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 

uint32_t
ldns_rdf2native_int32(const ldns_rdf *rd)
{
	uint32_t data;

	/* only allow 32 bit rdfs */
	if (ldns_rdf_size(rd) != LDNS_RDF_SIZE_DOUBLEWORD) {
		return 0;
	}
	
	memcpy(&data, ldns_rdf_data(rd), sizeof(data));
	return ntohl(data);
}