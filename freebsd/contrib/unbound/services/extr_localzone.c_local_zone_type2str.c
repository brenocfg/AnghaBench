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
typedef  enum localzone_type { ____Placeholder_localzone_type } localzone_type ;

/* Variables and functions */
#define  local_zone_always_nxdomain 142 
#define  local_zone_always_refuse 141 
#define  local_zone_always_transparent 140 
#define  local_zone_deny 139 
#define  local_zone_inform 138 
#define  local_zone_inform_deny 137 
#define  local_zone_inform_redirect 136 
#define  local_zone_nodefault 135 
#define  local_zone_noview 134 
#define  local_zone_redirect 133 
#define  local_zone_refuse 132 
#define  local_zone_static 131 
#define  local_zone_transparent 130 
#define  local_zone_typetransparent 129 
#define  local_zone_unset 128 

const char* local_zone_type2str(enum localzone_type t)
{
	switch(t) {
		case local_zone_unset: return "unset";
		case local_zone_deny: return "deny";
		case local_zone_refuse: return "refuse";
		case local_zone_redirect: return "redirect";
		case local_zone_transparent: return "transparent";
		case local_zone_typetransparent: return "typetransparent";
		case local_zone_static: return "static";
		case local_zone_nodefault: return "nodefault";
		case local_zone_inform: return "inform";
		case local_zone_inform_deny: return "inform_deny";
		case local_zone_inform_redirect: return "inform_redirect";
		case local_zone_always_transparent: return "always_transparent";
		case local_zone_always_refuse: return "always_refuse";
		case local_zone_always_nxdomain: return "always_nxdomain";
		case local_zone_noview: return "noview";
	}
	return "badtyped"; 
}