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
struct ucred {int dummy; } ;
struct radix_node_head {int /*<<< orphan*/  rh; int /*<<< orphan*/  (* rnh_deladdr ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct radix_node {int /*<<< orphan*/  rn_mask; int /*<<< orphan*/  rn_key; } ;
struct netcred {struct ucred* netc_anon; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NETADDR ; 
 int /*<<< orphan*/  crfree (struct ucred*) ; 
 int /*<<< orphan*/  free (struct radix_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
vfs_free_netcred(struct radix_node *rn, void *w)
{
	struct radix_node_head *rnh = (struct radix_node_head *) w;
	struct ucred *cred;

	(*rnh->rnh_deladdr) (rn->rn_key, rn->rn_mask, &rnh->rh);
	cred = ((struct netcred *)rn)->netc_anon;
	if (cred != NULL)
		crfree(cred);
	free(rn, M_NETADDR);
	return (0);
}