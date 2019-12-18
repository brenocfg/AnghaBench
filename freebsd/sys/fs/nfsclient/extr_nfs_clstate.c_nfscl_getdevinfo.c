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
struct nfscldevinfo {int /*<<< orphan*/  nfsdi_refcnt; } ;
struct nfsclclient {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFSLOCKCLSTATE () ; 
 int /*<<< orphan*/  NFSUNLOCKCLSTATE () ; 
 struct nfscldevinfo* nfscl_finddevinfo (struct nfsclclient*,int /*<<< orphan*/ *) ; 

struct nfscldevinfo *
nfscl_getdevinfo(struct nfsclclient *clp, uint8_t *deviceid,
    struct nfscldevinfo *dip)
{

	NFSLOCKCLSTATE();
	if (dip == NULL)
		dip = nfscl_finddevinfo(clp, deviceid);
	if (dip != NULL)
		dip->nfsdi_refcnt++;
	NFSUNLOCKCLSTATE();
	return (dip);
}