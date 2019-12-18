#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
struct TYPE_4__ {size_t _type; } ;
typedef  TYPE_1__ ldns_rr_descriptor ;

/* Variables and functions */
 size_t LDNS_RDATA_FIELD_DESCRIPTORS_COMMON ; 
 size_t LDNS_RDATA_FIELD_DESCRIPTORS_COUNT ; 
 TYPE_1__ const* rdata_field_descriptors ; 

const ldns_rr_descriptor *
ldns_rr_descript(uint16_t type)
{
	size_t i;
	if (type < LDNS_RDATA_FIELD_DESCRIPTORS_COMMON) {
		return &rdata_field_descriptors[type];
	} else {
		/* because not all array index equals type code */
		for (i = LDNS_RDATA_FIELD_DESCRIPTORS_COMMON;
		     i < LDNS_RDATA_FIELD_DESCRIPTORS_COUNT;
		     i++) {
		        if (rdata_field_descriptors[i]._type == type) {
		     		return &rdata_field_descriptors[i];
			}
		}
                return &rdata_field_descriptors[0];
	}
}