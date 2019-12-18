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
typedef  int /*<<< orphan*/  uint8_t ;
struct jailparam {size_t jp_valuelen; scalar_t__ jp_value; } ;
struct in_addr {int dummy; } ;
struct in6_addr {int dummy; } ;
typedef  int /*<<< orphan*/  ipbuf ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int INET6_ADDRSTRLEN ; 
 int /*<<< orphan*/ * inet_ntop (int,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  xo_close_list (char const*) ; 
 int /*<<< orphan*/  xo_emit (char const*,char*) ; 
 int /*<<< orphan*/  xo_err (int,char*) ; 
 int /*<<< orphan*/  xo_open_list (char const*) ; 

__attribute__((used)) static void
emit_ip_addr_list(int af_family, const char *list_name, struct jailparam *param)
{
	char ipbuf[INET6_ADDRSTRLEN];
	size_t addr_len;
	const char *emit_str;
	int ai, count;

	switch (af_family) {
	case AF_INET:
		addr_len = sizeof(struct in_addr);
		emit_str = "{P:        }{ql:ipv4_addr}{P:\n}";
		break;
	case AF_INET6:
		addr_len = sizeof(struct in6_addr);
		emit_str = "{P:        }{ql:ipv6_addr}{P:\n}";
		break;
	default:
		xo_err(1, "unsupported af_family");
		return;
	}

	count = param->jp_valuelen / addr_len;

	xo_open_list(list_name);
	for (ai = 0; ai < count; ai++) {
		if (inet_ntop(af_family,
		    ((uint8_t *)param->jp_value) + addr_len * ai,
		    ipbuf, sizeof(ipbuf)) == NULL) {
			xo_err(1, "inet_ntop");
		} else {
			xo_emit(emit_str, ipbuf);
		}
	}
	xo_close_list(list_name);
}