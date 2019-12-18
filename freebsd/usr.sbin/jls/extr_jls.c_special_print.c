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
struct jailparam {scalar_t__ jp_valuelen; int /*<<< orphan*/  jp_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int PRINT_NAMEVAL ; 
 int PRINT_QUOTED ; 
#define  XO_STYLE_JSON 129 
#define  XO_STYLE_XML 128 
 int /*<<< orphan*/  emit_ip_addr_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct jailparam*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xo_emit (char*) ; 
 int xo_get_style (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
special_print(int pflags, struct jailparam *param)
{
	int ip_as_list;

	switch (xo_get_style(NULL)) {
	case XO_STYLE_JSON:
	case XO_STYLE_XML:
		ip_as_list = 1;
		break;
	default:
		ip_as_list = 0;
	}

	if (!ip_as_list && param->jp_valuelen == 0) {
		if (pflags & PRINT_QUOTED)
			xo_emit("{P:\"\"}");
		else if (!(pflags & PRINT_NAMEVAL))
			xo_emit("{P:-}");
	} else if (ip_as_list && !strcmp(param->jp_name, "ip4.addr")) {
		emit_ip_addr_list(AF_INET, param->jp_name, param);
	} else if (ip_as_list && !strcmp(param->jp_name, "ip6.addr")) {
		emit_ip_addr_list(AF_INET6, param->jp_name, param);
	} else {
		return 0;
	}

	return 1;
}