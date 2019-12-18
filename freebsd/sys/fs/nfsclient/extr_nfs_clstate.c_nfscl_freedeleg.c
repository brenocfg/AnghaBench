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
struct nfscldeleghead {int dummy; } ;
struct nfscldeleg {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cldelegates; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct nfscldeleg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_NFSCLDELEG ; 
 int /*<<< orphan*/  TAILQ_REMOVE (struct nfscldeleghead*,struct nfscldeleg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct nfscldeleg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfscl_delegcnt ; 
 int /*<<< orphan*/  nfsdl_hash ; 
 int /*<<< orphan*/  nfsdl_list ; 
 TYPE_1__ nfsstatsv1 ; 

__attribute__((used)) static void
nfscl_freedeleg(struct nfscldeleghead *hdp, struct nfscldeleg *dp)
{

	TAILQ_REMOVE(hdp, dp, nfsdl_list);
	LIST_REMOVE(dp, nfsdl_hash);
	free(dp, M_NFSCLDELEG);
	nfsstatsv1.cldelegates--;
	nfscl_delegcnt--;
}