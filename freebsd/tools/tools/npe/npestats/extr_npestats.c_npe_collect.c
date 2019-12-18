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
struct npestats {int dummy; } ;
struct npestatfoo_p {int /*<<< orphan*/  oid; int /*<<< orphan*/  mib; } ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ sysctl (int /*<<< orphan*/ ,int,struct npestats*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
npe_collect(struct npestatfoo_p *wf, struct npestats *stats)
{
	size_t len = sizeof(struct npestats);
	if (sysctl(wf->mib, 4, stats, &len, NULL, 0) < 0)
		err(1, "sysctl: %s", wf->oid);
}