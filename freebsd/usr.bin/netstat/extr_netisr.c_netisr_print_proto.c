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
typedef  int /*<<< orphan*/  tmp ;
struct sysctl_netisr_proto {scalar_t__ snp_policy; int snp_flags; int /*<<< orphan*/  snp_dispatch; int /*<<< orphan*/  snp_qlimit; int /*<<< orphan*/  snp_proto; int /*<<< orphan*/  snp_name; } ;

/* Variables and functions */
 scalar_t__ NETISR_POLICY_CPU ; 
 scalar_t__ NETISR_POLICY_FLOW ; 
 scalar_t__ NETISR_POLICY_SOURCE ; 
 int NETISR_SNP_FLAGS_DRAINEDCPU ; 
 int NETISR_SNP_FLAGS_M2CPUID ; 
 int NETISR_SNP_FLAGS_M2FLOW ; 
 int /*<<< orphan*/  netisr_dispatch_policy_to_string (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  xo_emit (char*,char*,...) ; 

__attribute__((used)) static void
netisr_print_proto(struct sysctl_netisr_proto *snpp)
{
	char tmp[20];

	xo_emit("{[:-6}{k:name/%s}{]:}", snpp->snp_name);
	xo_emit(" {:protocol/%5u}", snpp->snp_proto);
	xo_emit(" {:queue-limit/%6u}", snpp->snp_qlimit);
	xo_emit(" {:policy-type/%6s}",
	    (snpp->snp_policy == NETISR_POLICY_SOURCE) ?  "source" :
	    (snpp->snp_policy == NETISR_POLICY_FLOW) ? "flow" :
	    (snpp->snp_policy == NETISR_POLICY_CPU) ? "cpu" : "-");
	netisr_dispatch_policy_to_string(snpp->snp_dispatch, tmp,
	    sizeof(tmp));
	xo_emit(" {:policy/%8s}", tmp);
	xo_emit("   {:flags/%s%s%s}\n",
	    (snpp->snp_flags & NETISR_SNP_FLAGS_M2CPUID) ?  "C" : "-",
	    (snpp->snp_flags & NETISR_SNP_FLAGS_DRAINEDCPU) ?  "D" : "-",
	    (snpp->snp_flags & NETISR_SNP_FLAGS_M2FLOW) ? "F" : "-");
}