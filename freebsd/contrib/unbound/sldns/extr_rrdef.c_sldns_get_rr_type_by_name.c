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
typedef  int sldns_rr_type ;
struct TYPE_3__ {char* _name; int _type; } ;
typedef  TYPE_1__ sldns_rr_descriptor ;

/* Variables and functions */
 scalar_t__ LDNS_RDATA_FIELD_DESCRIPTORS_COUNT ; 
 int atoi (char const*) ; 
 TYPE_1__* rdata_field_descriptors ; 
 int strlen (char const*) ; 
 scalar_t__ strncasecmp (char const*,char const*,int) ; 

sldns_rr_type
sldns_get_rr_type_by_name(const char *name)
{
	unsigned int i;
	const char *desc_name;
	const sldns_rr_descriptor *desc;

	/* TYPEXX representation */
	if (strlen(name) > 4 && strncasecmp(name, "TYPE", 4) == 0) {
		return atoi(name + 4);
	}

	/* Normal types */
	for (i = 0; i < (unsigned int) LDNS_RDATA_FIELD_DESCRIPTORS_COUNT; i++) {
		desc = &rdata_field_descriptors[i];
		desc_name = desc->_name;
		if(desc_name &&
		   strlen(name) == strlen(desc_name) &&
		   strncasecmp(name, desc_name, strlen(desc_name)) == 0) {
			/* because not all array index equals type code */
			return desc->_type;
		}
	}

	/* special cases for query types */
	if (strlen(name) == 4 && strncasecmp(name, "IXFR", 4) == 0) {
		return 251;
	} else if (strlen(name) == 4 && strncasecmp(name, "AXFR", 4) == 0) {
		return 252;
	} else if (strlen(name) == 5 && strncasecmp(name, "MAILB", 5) == 0) {
		return 253;
	} else if (strlen(name) == 5 && strncasecmp(name, "MAILA", 5) == 0) {
		return 254;
	} else if (strlen(name) == 3 && strncasecmp(name, "ANY", 3) == 0) {
		return 255;
	}

	return 0;
}