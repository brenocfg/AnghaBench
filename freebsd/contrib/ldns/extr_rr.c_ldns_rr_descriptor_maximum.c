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
struct TYPE_3__ {scalar_t__ _variable; size_t _maximum; } ;
typedef  TYPE_1__ ldns_rr_descriptor ;

/* Variables and functions */
 scalar_t__ LDNS_RDF_TYPE_NONE ; 
 size_t UINT_MAX ; 

size_t
ldns_rr_descriptor_maximum(const ldns_rr_descriptor *descriptor)
{
	if (descriptor) {
		if (descriptor->_variable != LDNS_RDF_TYPE_NONE) {
			/* Should really be SIZE_MAX... bad FreeBSD.  */
			return UINT_MAX;
		} else {
			return descriptor->_maximum;
		}
	} else {
		return 0;
	}
}