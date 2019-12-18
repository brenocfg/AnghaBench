#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nfsrvcache {int rc_flag; int /*<<< orphan*/  rc_xid; } ;
struct mtx {int dummy; } ;
struct TYPE_2__ {struct mtx mtx; } ;

/* Variables and functions */
 int RC_UDP ; 
 size_t nfsrc_hash (int /*<<< orphan*/ ) ; 
 struct mtx nfsrc_udpmtx ; 
 TYPE_1__* nfsrchash_table ; 

__attribute__((used)) static __inline struct mtx *
nfsrc_cachemutex(struct nfsrvcache *rp)
{

	if ((rp->rc_flag & RC_UDP) != 0)
		return (&nfsrc_udpmtx);
	return (&nfsrchash_table[nfsrc_hash(rp->rc_xid)].mtx);
}