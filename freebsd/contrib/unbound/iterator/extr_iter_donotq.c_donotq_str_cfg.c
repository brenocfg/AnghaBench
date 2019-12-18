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
struct sockaddr_storage {int dummy; } ;
struct iter_donotq {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  UNBOUND_DNS_PORT ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  donotq_insert (struct iter_donotq*,struct sockaddr_storage*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  log_err (char*,...) ; 
 int /*<<< orphan*/  netblockstrtoaddr (char const*,int /*<<< orphan*/ ,struct sockaddr_storage*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static int
donotq_str_cfg(struct iter_donotq* dq, const char* str)
{
	struct sockaddr_storage addr;
	int net;
	socklen_t addrlen;
	verbose(VERB_ALGO, "donotq: %s", str);
	if(!netblockstrtoaddr(str, UNBOUND_DNS_PORT, &addr, &addrlen, &net)) {
		log_err("cannot parse donotquery netblock: %s", str);
		return 0;
	}
	if(!donotq_insert(dq, &addr, addrlen, net)) {
		log_err("out of memory");
		return 0;
	}
	return 1;
}