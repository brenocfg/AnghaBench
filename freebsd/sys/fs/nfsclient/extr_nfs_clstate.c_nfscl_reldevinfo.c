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
struct nfscldevinfo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFSLOCKCLSTATE () ; 
 int /*<<< orphan*/  NFSUNLOCKCLSTATE () ; 
 int /*<<< orphan*/  nfscl_reldevinfo_locked (struct nfscldevinfo*) ; 

void
nfscl_reldevinfo(struct nfscldevinfo *dip)
{

	NFSLOCKCLSTATE();
	nfscl_reldevinfo_locked(dip);
	NFSUNLOCKCLSTATE();
}