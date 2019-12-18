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
typedef  int /*<<< orphan*/  ldns_rdf ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 size_t* ldns_rdf_data (int /*<<< orphan*/  const*) ; 
 size_t ldns_rdf_size (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static bool
ldns_dname_last_label_is_root_label(const ldns_rdf* dname)
{
	size_t src_pos;
	size_t len = 0;

	for (src_pos = 0; src_pos < ldns_rdf_size(dname); src_pos += len + 1) {
		len = ldns_rdf_data(dname)[src_pos];
	}
	assert(src_pos == ldns_rdf_size(dname));

	return src_pos > 0 && len == 0;
}