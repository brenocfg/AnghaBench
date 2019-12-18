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
typedef  scalar_t__ sldns_rdf_type ;

/* Variables and functions */
 scalar_t__ LDNS_RDF_TYPE_LONG_STR ; 
 scalar_t__ LDNS_RDF_TYPE_STR ; 

__attribute__((used)) static int
sldns_rdf_type_maybe_quoted(sldns_rdf_type rdf_type)
{
	return  rdf_type == LDNS_RDF_TYPE_STR ||
		rdf_type == LDNS_RDF_TYPE_LONG_STR;
}