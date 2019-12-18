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
struct eap_method {int version; int vendor; char const* name; int /*<<< orphan*/  method; } ;
typedef  int /*<<< orphan*/  EapType ;

/* Variables and functions */
 struct eap_method* os_zalloc (int) ; 

struct eap_method * eap_peer_method_alloc(int version, int vendor,
					  EapType method, const char *name)
{
	struct eap_method *eap;
	eap = os_zalloc(sizeof(*eap));
	if (eap == NULL)
		return NULL;
	eap->version = version;
	eap->vendor = vendor;
	eap->method = method;
	eap->name = name;
	return eap;
}