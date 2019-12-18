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
typedef  int /*<<< orphan*/  EapType ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_TYPE_NONE ; 
 int EAP_VENDOR_IETF ; 

__attribute__((used)) static inline EapType eap_peer_get_type(const char *name, int *vendor)
{
	*vendor = EAP_VENDOR_IETF;
	return EAP_TYPE_NONE;
}