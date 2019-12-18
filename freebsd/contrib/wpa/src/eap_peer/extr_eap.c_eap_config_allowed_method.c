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
typedef  scalar_t__ u32 ;
struct eap_sm {int dummy; } ;
struct eap_peer_config {struct eap_method_type* eap_methods; } ;
struct eap_method_type {int vendor; scalar_t__ method; } ;

/* Variables and functions */
 scalar_t__ EAP_TYPE_NONE ; 
 int EAP_VENDOR_IETF ; 

__attribute__((used)) static int eap_config_allowed_method(struct eap_sm *sm,
				     struct eap_peer_config *config,
				     int vendor, u32 method)
{
	int i;
	struct eap_method_type *m;

	if (config == NULL || config->eap_methods == NULL)
		return 1;

	m = config->eap_methods;
	for (i = 0; m[i].vendor != EAP_VENDOR_IETF ||
		     m[i].method != EAP_TYPE_NONE; i++) {
		if (m[i].vendor == vendor && m[i].method == method)
			return 1;
	}
	return 0;
}