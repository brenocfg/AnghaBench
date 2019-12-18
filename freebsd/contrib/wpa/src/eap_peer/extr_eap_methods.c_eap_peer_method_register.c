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
struct eap_method {scalar_t__ version; scalar_t__ vendor; scalar_t__ method; struct eap_method* next; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 scalar_t__ EAP_PEER_METHOD_INTERFACE_VERSION ; 
 struct eap_method* eap_methods ; 
 int /*<<< orphan*/  eap_peer_method_free (struct eap_method*) ; 
 scalar_t__ os_strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int eap_peer_method_register(struct eap_method *method)
{
	struct eap_method *m, *last = NULL;

	if (method == NULL || method->name == NULL ||
	    method->version != EAP_PEER_METHOD_INTERFACE_VERSION) {
		eap_peer_method_free(method);
		return -1;
	}

	for (m = eap_methods; m; m = m->next) {
		if ((m->vendor == method->vendor &&
		     m->method == method->method) ||
		    os_strcmp(m->name, method->name) == 0) {
			eap_peer_method_free(method);
			return -2;
		}
		last = m;
	}

	if (last)
		last->next = method;
	else
		eap_methods = method;

	return 0;
}