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
typedef  int /*<<< orphan*/  ldns_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  ldns_rdf2buffer_str_int8 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

ldns_status
ldns_rdf2buffer_str_alg(ldns_buffer *output, const ldns_rdf *rdf)
{
	return ldns_rdf2buffer_str_int8(output, rdf);
}