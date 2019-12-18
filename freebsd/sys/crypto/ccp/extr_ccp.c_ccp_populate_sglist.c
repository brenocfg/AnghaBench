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
struct sglist {int dummy; } ;
struct cryptop {int crp_flags; int /*<<< orphan*/  crp_ilen; int /*<<< orphan*/  crp_buf; int /*<<< orphan*/  crp_uio; int /*<<< orphan*/  crp_mbuf; } ;

/* Variables and functions */
 int CRYPTO_F_IMBUF ; 
 int CRYPTO_F_IOV ; 
 int sglist_append (struct sglist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sglist_append_mbuf (struct sglist*,int /*<<< orphan*/ ) ; 
 int sglist_append_uio (struct sglist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sglist_reset (struct sglist*) ; 

__attribute__((used)) static int
ccp_populate_sglist(struct sglist *sg, struct cryptop *crp)
{
	int error;

	sglist_reset(sg);
	if (crp->crp_flags & CRYPTO_F_IMBUF)
		error = sglist_append_mbuf(sg, crp->crp_mbuf);
	else if (crp->crp_flags & CRYPTO_F_IOV)
		error = sglist_append_uio(sg, crp->crp_uio);
	else
		error = sglist_append(sg, crp->crp_buf, crp->crp_ilen);
	return (error);
}