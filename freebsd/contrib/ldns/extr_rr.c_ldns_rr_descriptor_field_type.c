#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t _maximum; scalar_t__ _variable; scalar_t__* _wireformat; } ;
typedef  TYPE_1__ ldns_rr_descriptor ;
typedef  scalar_t__ ldns_rdf_type ;

/* Variables and functions */
 scalar_t__ LDNS_RDF_TYPE_NONE ; 
 int /*<<< orphan*/  assert (int) ; 

ldns_rdf_type
ldns_rr_descriptor_field_type(const ldns_rr_descriptor *descriptor,
                              size_t index)
{
	assert(descriptor != NULL);
	assert(index < descriptor->_maximum
	       || descriptor->_variable != LDNS_RDF_TYPE_NONE);
	if (index < descriptor->_maximum) {
		return descriptor->_wireformat[index];
	} else {
		return descriptor->_variable;
	}
}