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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  sysid ;
struct nlm_sm_status {int /*<<< orphan*/  state; int /*<<< orphan*/  priv; int /*<<< orphan*/  mon_name; } ;
struct nlm_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NLM_DEBUG (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct nlm_host* nlm_find_host_by_sysid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_host_notify (struct nlm_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_host_release (struct nlm_host*) ; 

void
nlm_sm_notify(struct nlm_sm_status *argp)
{
	uint32_t sysid;
	struct nlm_host *host;

	NLM_DEBUG(3, "nlm_sm_notify(): mon_name = %s\n", argp->mon_name);
	memcpy(&sysid, &argp->priv, sizeof(sysid));
	host = nlm_find_host_by_sysid(sysid);
	if (host) {
		nlm_host_notify(host, argp->state);
		nlm_host_release(host);
	}
}