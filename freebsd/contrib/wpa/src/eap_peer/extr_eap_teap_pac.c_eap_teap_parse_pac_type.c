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
struct eap_teap_pac {scalar_t__ pac_type; } ;

/* Variables and functions */
 scalar_t__ PAC_TYPE_TUNNEL_PAC ; 
 scalar_t__ atoi (char*) ; 

__attribute__((used)) static const char * eap_teap_parse_pac_type(struct eap_teap_pac *pac,
					    char *pos)
{
	if (!pos)
		return "Cannot parse pac type";
	pac->pac_type = atoi(pos);
	if (pac->pac_type != PAC_TYPE_TUNNEL_PAC)
		return "Unrecognized PAC-Type";

	return NULL;
}