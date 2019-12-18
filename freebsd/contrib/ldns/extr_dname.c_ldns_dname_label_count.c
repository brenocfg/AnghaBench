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
typedef  scalar_t__ uint8_t ;
typedef  size_t uint16_t ;
typedef  int /*<<< orphan*/  ldns_rdf ;

/* Variables and functions */
 scalar_t__ LDNS_RDF_TYPE_DNAME ; 
 size_t* ldns_rdf_data (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_rdf_get_type (int /*<<< orphan*/  const*) ; 
 size_t ldns_rdf_size (int /*<<< orphan*/  const*) ; 

uint8_t
ldns_dname_label_count(const ldns_rdf *r)
{
        uint16_t src_pos;
        uint16_t len;
        uint8_t i;
        size_t r_size;

	if (!r) {
		return 0;
	}

	i = 0;
	src_pos = 0;
	r_size = ldns_rdf_size(r);

	if (ldns_rdf_get_type(r) != LDNS_RDF_TYPE_DNAME) {
		return 0;
	} else {
		len = ldns_rdf_data(r)[src_pos]; /* start of the label */

		/* single root label */
		if (1 == r_size) {
			return 0;
		} else {
			while ((len > 0) && src_pos < r_size) {
				src_pos++;
				src_pos += len;
				len = ldns_rdf_data(r)[src_pos];
				i++;
			}
		}
	}
	return i;
}