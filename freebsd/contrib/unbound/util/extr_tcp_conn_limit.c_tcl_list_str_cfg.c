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
typedef  scalar_t__ uint32_t ;
struct tcl_list {int dummy; } ;
struct sockaddr_storage {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  UNBOUND_DNS_PORT ; 
 scalar_t__ atoi (char const*) ; 
 int /*<<< orphan*/  log_err (char*,...) ; 
 int /*<<< orphan*/  netblockstrtoaddr (char const*,int /*<<< orphan*/ ,struct sockaddr_storage*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  tcl_list_insert (struct tcl_list*,struct sockaddr_storage*,int /*<<< orphan*/ ,int,scalar_t__,int) ; 

__attribute__((used)) static int
tcl_list_str_cfg(struct tcl_list* tcl, const char* str, const char* s2,
	int complain_duplicates)
{
	struct sockaddr_storage addr;
	int net;
	socklen_t addrlen;
	uint32_t limit;
	if(atoi(s2) < 0) {
		log_err("bad connection limit %s", s2);
		return 0;
	}
	limit = (uint32_t)atoi(s2);
	if(!netblockstrtoaddr(str, UNBOUND_DNS_PORT, &addr, &addrlen, &net)) {
		log_err("cannot parse connection limit netblock: %s", str);
		return 0;
	}
	if(!tcl_list_insert(tcl, &addr, addrlen, net, limit,
		complain_duplicates)) {
		log_err("out of memory");
		return 0;
	}
	return 1;
}