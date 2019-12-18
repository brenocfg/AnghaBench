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
struct config_file {int num_ifs; int num_out_ifs; int /*<<< orphan*/ * out_ifs; int /*<<< orphan*/ * ifs; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  UNBOUND_DNS_PORT ; 
 int /*<<< orphan*/  extstrtoaddr (int /*<<< orphan*/ ,struct sockaddr_storage*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fatal_exit (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipstrtoaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sockaddr_storage*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netblockstrtoaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sockaddr_storage*,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
interfacechecks(struct config_file* cfg)
{
	int d;
	struct sockaddr_storage a;
	socklen_t alen;
	int i, j;
	for(i=0; i<cfg->num_ifs; i++) {
		if(!extstrtoaddr(cfg->ifs[i], &a, &alen)) {
			fatal_exit("cannot parse interface specified as '%s'",
				cfg->ifs[i]);
		}
		for(j=0; j<cfg->num_ifs; j++) {
			if(i!=j && strcmp(cfg->ifs[i], cfg->ifs[j])==0)
				fatal_exit("interface: %s present twice, "
					"cannot bind same ports twice.",
					cfg->ifs[i]);
		}
	}
	for(i=0; i<cfg->num_out_ifs; i++) {
		if(!ipstrtoaddr(cfg->out_ifs[i], UNBOUND_DNS_PORT, &a, &alen) &&
		   !netblockstrtoaddr(cfg->out_ifs[i], UNBOUND_DNS_PORT, &a, &alen, &d)) {
			fatal_exit("cannot parse outgoing-interface "
				"specified as '%s'", cfg->out_ifs[i]);
		}
		for(j=0; j<cfg->num_out_ifs; j++) {
			if(i!=j && strcmp(cfg->out_ifs[i], cfg->out_ifs[j])==0)
				fatal_exit("outgoing-interface: %s present "
					"twice, cannot bind same ports twice.",
					cfg->out_ifs[i]);
		}
	}
}