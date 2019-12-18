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
typedef  int uint16_t ;

/* Variables and functions */
#define  LDNS_RR_TYPE_KX 135 
#define  LDNS_RR_TYPE_MB 134 
#define  LDNS_RR_TYPE_MD 133 
#define  LDNS_RR_TYPE_MF 132 
#define  LDNS_RR_TYPE_MX 131 
#define  LDNS_RR_TYPE_NAPTR 130 
#define  LDNS_RR_TYPE_NS 129 
#define  LDNS_RR_TYPE_SRV 128 

__attribute__((used)) static int
has_additional(uint16_t t)
{
	switch(t) {
		case LDNS_RR_TYPE_MB:
		case LDNS_RR_TYPE_MD:
		case LDNS_RR_TYPE_MF:
		case LDNS_RR_TYPE_NS:
		case LDNS_RR_TYPE_MX:
		case LDNS_RR_TYPE_KX:
		case LDNS_RR_TYPE_SRV:
			return 1;
		case LDNS_RR_TYPE_NAPTR:
			/* TODO: NAPTR not supported, glue stripped off */
			return 0;
	}
	return 0;
}