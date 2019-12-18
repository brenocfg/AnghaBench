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
struct nfslayouthead {int dummy; } ;
struct nfslayout {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NFSDSTATE ; 
 int /*<<< orphan*/  NFSD_DEBUG (int,char*,struct nfslayout*) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (struct nfslayouthead*,struct nfslayout*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (struct nfslayout*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lay_list ; 
 int /*<<< orphan*/  nfsrv_layoutcnt ; 

__attribute__((used)) static void
nfsrv_freelayout(struct nfslayouthead *lhp, struct nfslayout *lyp)
{

	NFSD_DEBUG(4, "Freelayout=%p\n", lyp);
	atomic_add_int(&nfsrv_layoutcnt, -1);
	TAILQ_REMOVE(lhp, lyp, lay_list);
	free(lyp, M_NFSDSTATE);
}