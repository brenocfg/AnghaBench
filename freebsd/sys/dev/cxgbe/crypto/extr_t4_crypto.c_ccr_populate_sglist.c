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
struct uio {int dummy; } ;
struct sglist {int dummy; } ;
struct mbuf {int dummy; } ;
struct cryptop {int crp_flags; int /*<<< orphan*/  crp_ilen; scalar_t__ crp_buf; } ;

/* Variables and functions */
 int CRYPTO_F_IMBUF ; 
 int CRYPTO_F_IOV ; 
 int sglist_append (struct sglist*,scalar_t__,int /*<<< orphan*/ ) ; 
 int sglist_append_mbuf (struct sglist*,struct mbuf*) ; 
 int sglist_append_uio (struct sglist*,struct uio*) ; 
 int /*<<< orphan*/  sglist_reset (struct sglist*) ; 

__attribute__((used)) static int
ccr_populate_sglist(struct sglist *sg, struct cryptop *crp)
{
	int error;

	sglist_reset(sg);
	if (crp->crp_flags & CRYPTO_F_IMBUF)
		error = sglist_append_mbuf(sg, (struct mbuf *)crp->crp_buf);
	else if (crp->crp_flags & CRYPTO_F_IOV)
		error = sglist_append_uio(sg, (struct uio *)crp->crp_buf);
	else
		error = sglist_append(sg, crp->crp_buf, crp->crp_ilen);
	return (error);
}