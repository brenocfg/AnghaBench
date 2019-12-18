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
struct iter_forwards {int dummy; } ;
struct delegpt {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  RES ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_CLASS_IN ; 
 struct delegpt* forwards_lookup (struct iter_forwards*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_assert (int) ; 
 scalar_t__ query_dname_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ssl_print_name_dp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct delegpt*) ; 
 int ssl_printf (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
print_root_fwds(RES* ssl, struct iter_forwards* fwds, uint8_t* root)
{
	struct delegpt* dp;
	dp = forwards_lookup(fwds, root, LDNS_RR_CLASS_IN);
	if(!dp)
		return ssl_printf(ssl, "off (using root hints)\n");
	/* if dp is returned it must be the root */
	log_assert(query_dname_compare(dp->name, root)==0);
	return ssl_print_name_dp(ssl, NULL, root, LDNS_RR_CLASS_IN, dp);
}