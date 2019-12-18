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
struct vop_cachedlookup_args {int dummy; } ;

/* Variables and functions */
 int mqfs_lookupx (struct vop_cachedlookup_args*) ; 

__attribute__((used)) static int
mqfs_lookup(struct vop_cachedlookup_args *ap)
{
	int rc;

	rc = mqfs_lookupx(ap);
	return (rc);
}