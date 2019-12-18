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
struct eap_method {int vendor; int /*<<< orphan*/  method; int /*<<< orphan*/  name; struct eap_method* next; } ;
typedef  int /*<<< orphan*/  EapType ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_TYPE_NONE ; 
 int EAP_VENDOR_IETF ; 
 struct eap_method* eap_methods ; 
 scalar_t__ os_strcmp (int /*<<< orphan*/ ,char const*) ; 

EapType eap_peer_get_type(const char *name, int *vendor)
{
	struct eap_method *m;
	for (m = eap_methods; m; m = m->next) {
		if (os_strcmp(m->name, name) == 0) {
			*vendor = m->vendor;
			return m->method;
		}
	}
	*vendor = EAP_VENDOR_IETF;
	return EAP_TYPE_NONE;
}