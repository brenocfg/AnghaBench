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
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_rdf ;
typedef  int /*<<< orphan*/  ldns_rbtree_t ;
typedef  int /*<<< orphan*/  ldns_buffer ;

/* Variables and functions */
 scalar_t__ LDNS_RDF_TYPE_DNAME ; 
 scalar_t__ ldns_buffer_reserve (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_buffer_status (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_buffer_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_dname2buffer_wire_compress (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rdf_data (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_rdf_get_type (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rdf_size (int /*<<< orphan*/  const*) ; 

ldns_status
ldns_rdf2buffer_wire_compress(ldns_buffer *buffer, const ldns_rdf *rdf, ldns_rbtree_t *compression_data)
{
	/* If it's a DNAME, call that function to get compression */
	if(compression_data && ldns_rdf_get_type(rdf) == LDNS_RDF_TYPE_DNAME)
	{
		return ldns_dname2buffer_wire_compress(buffer,rdf,compression_data);
	}

	if (ldns_buffer_reserve(buffer, ldns_rdf_size(rdf))) {
		ldns_buffer_write(buffer, ldns_rdf_data(rdf), ldns_rdf_size(rdf));
	}
	return ldns_buffer_status(buffer);
}