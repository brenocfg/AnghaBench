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
struct eap_teap_pac {int /*<<< orphan*/  pac_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAC_TYPE_TUNNEL_PAC ; 
 struct eap_teap_pac* os_zalloc (int) ; 

__attribute__((used)) static const char * eap_teap_parse_start(struct eap_teap_pac **pac)
{
	if (*pac)
		return "START line without END";

	*pac = os_zalloc(sizeof(struct eap_teap_pac));
	if (!(*pac))
		return "No memory for PAC entry";
	(*pac)->pac_type = PAC_TYPE_TUNNEL_PAC;
	return NULL;
}