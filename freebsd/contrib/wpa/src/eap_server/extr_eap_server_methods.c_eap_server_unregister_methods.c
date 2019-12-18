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
struct eap_method {int /*<<< orphan*/  (* free ) (struct eap_method*) ;struct eap_method* next; } ;

/* Variables and functions */
 struct eap_method* eap_methods ; 
 int /*<<< orphan*/  eap_server_method_free (struct eap_method*) ; 
 int /*<<< orphan*/  stub1 (struct eap_method*) ; 

void eap_server_unregister_methods(void)
{
	struct eap_method *m;

	while (eap_methods) {
		m = eap_methods;
		eap_methods = eap_methods->next;

		if (m->free)
			m->free(m);
		else
			eap_server_method_free(m);
	}
}