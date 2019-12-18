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
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  ldns_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  ldns_buffer_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  ldns_buffer_status (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rdf_data (int /*<<< orphan*/ ) ; 
 size_t ldns_rdf_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_get_type (int /*<<< orphan*/  const*) ; 
 size_t ldns_rr_rd_count (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rr_rdf (int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static ldns_status
ldns_rr2buffer_str_rfc3597(ldns_buffer *output, const ldns_rr *rr)
{
	size_t total_rdfsize = 0;
	size_t i, j;

	ldns_buffer_printf(output, "TYPE%u\t", ldns_rr_get_type(rr));
	for (i = 0; i < ldns_rr_rd_count(rr); i++) {
		total_rdfsize += ldns_rdf_size(ldns_rr_rdf(rr, i));
	}
	if (total_rdfsize == 0) {
		ldns_buffer_printf(output, "\\# 0\n");
		return ldns_buffer_status(output);
	}
	ldns_buffer_printf(output, "\\# %d ", total_rdfsize);
	for (i = 0; i < ldns_rr_rd_count(rr); i++) {
		for (j = 0; j < ldns_rdf_size(ldns_rr_rdf(rr, i)); j++) {
			ldns_buffer_printf(output, "%.2x",
					ldns_rdf_data(ldns_rr_rdf(rr, i))[j]);
		}
	}
	ldns_buffer_printf(output, "\n");
	return ldns_buffer_status(output);
}