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
struct eap_method {int vendor; scalar_t__ method; char const* name; struct eap_method* next; } ;
typedef  scalar_t__ EapType ;

/* Variables and functions */
 scalar_t__ EAP_TYPE_EXPANDED ; 
 int EAP_VENDOR_IETF ; 
 struct eap_method* eap_methods ; 

const char * eap_get_name(int vendor, EapType type)
{
	struct eap_method *m;
	if (vendor == EAP_VENDOR_IETF && type == EAP_TYPE_EXPANDED)
		return "expanded";
	for (m = eap_methods; m; m = m->next) {
		if (m->vendor == vendor && m->method == type)
			return m->name;
	}
	return NULL;
}