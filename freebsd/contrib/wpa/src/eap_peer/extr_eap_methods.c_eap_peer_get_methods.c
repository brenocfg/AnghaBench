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
typedef  struct eap_method {struct eap_method const* next; } const eap_method ;

/* Variables and functions */
 struct eap_method const* eap_methods ; 

const struct eap_method * eap_peer_get_methods(size_t *count)
{
	int c = 0;
	struct eap_method *m;

	for (m = eap_methods; m; m = m->next)
		c++;
	
	*count = c;
	return eap_methods;
}