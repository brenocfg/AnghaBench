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
struct nfsdevice {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct nfsdevice*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsdev_list ; 
 int /*<<< orphan*/  nfsrv_devidhead ; 
 int /*<<< orphan*/  nfsrv_freeonedevid (struct nfsdevice*) ; 

__attribute__((used)) static void
nfsrv_freedevid(struct nfsdevice *ds)
{

	TAILQ_REMOVE(&nfsrv_devidhead, ds, nfsdev_list);
	nfsrv_freeonedevid(ds);
}