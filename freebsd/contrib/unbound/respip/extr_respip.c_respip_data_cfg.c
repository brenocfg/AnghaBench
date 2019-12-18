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
struct respip_set {int /*<<< orphan*/  region; } ;
struct resp_addr {scalar_t__ action; } ;

/* Variables and functions */
 int /*<<< orphan*/  log_err (char*,char const*,char const*) ; 
 int respip_enter_rr (int /*<<< orphan*/ ,struct resp_addr*,char const*,char const*) ; 
 struct resp_addr* respip_find_or_create (struct respip_set*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ respip_none ; 

__attribute__((used)) static int
respip_data_cfg(struct respip_set* set, const char* ipstr, const char* rrstr)
{
	struct resp_addr* node;

	node=respip_find_or_create(set, ipstr, 0);
	if(!node || node->action == respip_none) {
		log_err("cannot parse response-ip-data %s: "
			"response-ip node for %s not found", rrstr, ipstr);
		return 0;
	}
	return respip_enter_rr(set->region, node, rrstr, ipstr);
}