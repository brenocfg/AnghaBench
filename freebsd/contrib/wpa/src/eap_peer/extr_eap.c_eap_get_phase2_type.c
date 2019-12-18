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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_TYPE_NONE ; 
 int EAP_VENDOR_IETF ; 
 scalar_t__ eap_allowed_phase2_type (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_peer_get_type (char const*,int*) ; 

u32 eap_get_phase2_type(const char *name, int *vendor)
{
	int v;
	u32 type = eap_peer_get_type(name, &v);
	if (eap_allowed_phase2_type(v, type)) {
		*vendor = v;
		return type;
	}
	*vendor = EAP_VENDOR_IETF;
	return EAP_TYPE_NONE;
}