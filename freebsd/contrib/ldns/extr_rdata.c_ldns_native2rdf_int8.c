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
typedef  int /*<<< orphan*/  ldns_rdf_type ;
typedef  int /*<<< orphan*/  ldns_rdf ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RDF_SIZE_BYTE ; 
 int /*<<< orphan*/ * ldns_rdf_new_frm_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

ldns_rdf *
ldns_native2rdf_int8(ldns_rdf_type type, uint8_t value)
{
	return ldns_rdf_new_frm_data(type, LDNS_RDF_SIZE_BYTE, &value);
}