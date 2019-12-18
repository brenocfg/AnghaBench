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
typedef  int /*<<< orphan*/  uint16_t ;
struct delegpt_ns {int /*<<< orphan*/ * name; struct delegpt_ns* next; } ;
struct delegpt_addr {int /*<<< orphan*/  addrlen; int /*<<< orphan*/  addr; struct delegpt_addr* next_target; } ;
struct delegpt {struct delegpt_addr* target_list; struct delegpt_ns* nslist; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  RES ;

/* Variables and functions */
 int /*<<< orphan*/  addr_to_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dname_str (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* sldns_wire2str_class (int /*<<< orphan*/ ) ; 
 int ssl_printf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static int
ssl_print_name_dp(RES* ssl, const char* str, uint8_t* nm, uint16_t dclass,
	struct delegpt* dp)
{
	char buf[257];
	struct delegpt_ns* ns;
	struct delegpt_addr* a;
	int f = 0;
	if(str) { /* print header for forward, stub */
		char* c = sldns_wire2str_class(dclass);
		dname_str(nm, buf);
		if(!ssl_printf(ssl, "%s %s %s ", buf, (c?c:"CLASS??"), str)) {
			free(c);
			return 0;
		}
		free(c);
	}
	for(ns = dp->nslist; ns; ns = ns->next) {
		dname_str(ns->name, buf);
		if(!ssl_printf(ssl, "%s%s", (f?" ":""), buf))
			return 0;
		f = 1;
	}
	for(a = dp->target_list; a; a = a->next_target) {
		addr_to_str(&a->addr, a->addrlen, buf, sizeof(buf));
		if(!ssl_printf(ssl, "%s%s", (f?" ":""), buf))
			return 0;
		f = 1;
	}
	return ssl_printf(ssl, "\n");
}